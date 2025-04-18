import os
import csv
import subprocess
import logging
from tempfile import NamedTemporaryFile
import shutil
from pathlib import Path
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("csv_path", help="")
args = parser.parse_args()
csv_path = args.csv_path

logging.basicConfig(
    filename= os.path.join(os.path.dirname(csv_path), "job_monitor.log"),
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

def get_job_status(cluster_id):
    try:
        q_result = subprocess.run(
            f"hep_q -i {cluster_id}",
            shell=True, capture_output=True, text=True, check=True
        )
        if ", 0 held," in q_result.stdout:
            logging.info(f"Cluster {cluster_id} 没有挂起作业")
            if ", 0 idle," in q_result.stdout:
                logging.info(f"Cluster {cluster_id} 作业全部脱离排队")
                if "0 jobs" in q_result.stdout and ", 0 suspended" in q_result.stdout:
                    logging.info(f"Cluster {cluster_id} 作业全部完成")
                    return "completed"
        else:
            logging.info(f"Cluster {cluster_id} 有挂起作业，尝试释放")
            subprocess.run(
                f"hep_q -release {cluster_id}",
                shell=True, check=True
            )
    except subprocess.CalledProcessError as e:
        logging.error(f"查询作业状态失败: {e}")
        return "error"

def update_csv_status(csv_path, cluster_id, new_status):
    tempfile = NamedTemporaryFile(mode='w', delete=False)
    
    with open(csv_path, 'r') as csvfile, tempfile:
        reader = csv.reader(csvfile)
        writer = csv.writer(tempfile)
        
        for row in reader:
            if len(row) >= 4 and row[0] == cluster_id:
                row[3] = str(new_status)
                logging.info(f"更新集群 {cluster_id} 状态为 {new_status}")
            writer.writerow(row)

    shutil.move(tempfile.name, csv_path)

def process_clusters(csv_path):
    # 创建临时文件处理中间状态
    temp_path = csv_path + '.tmp'
    processed = False
    ifAlljobFinished = True
    try:
        with open(csv_path, 'r') as infile, open(temp_path, 'w', newline='') as outfile:
            reader = csv.reader(infile)
            writer = csv.writer(outfile)
            
            for row in reader:
                if len(row) < 4:
                    continue
                
                cluster_id, log_dir, script_dir, status = row[0], row[1], row[2], row[3]
                if status == '1':
                    writer.writerow(row)
                    continue
                ifAlljobFinished = False
                current_status = get_job_status(cluster_id)
                if current_status == "completed":
                    if pack_and_clean(log_dir, script_dir, cluster_id):
                            row[3] = '1'
                            processed = True
                else:
                    logging.warning(f"Cluster {cluster_id} 存在失败或未完成作业，保持未处理状态")
                
                writer.writerow(row)
        
        if processed:
            shutil.move(temp_path, csv_path)
        else:
            os.remove(temp_path)
        return ifAlljobFinished
            
    except Exception as e:
        logging.error(f"处理过程中断: {e}")
        if os.path.exists(temp_path):
            os.remove(temp_path)
        return True

def pack_and_clean(log_dir, script_dir, cluster_id):
    try:
        tar_path = Path(log_dir).parent / f"job_logs_{cluster_id}.tar.gz"
        
        subprocess.run(
            f"tar -czf {tar_path} -C {log_dir} .",
            shell=True, check=True
        )
        logging.info(f"已打包日志: {tar_path}")
        
        subprocess.run(f"rm -rf {log_dir}", shell=True, check=True)
        subprocess.run(f"rm -rf {script_dir}", shell=True, check=True)
        logging.info(f"已清理目录: {log_dir} 和 {script_dir}")
        
        return True
    except Exception as e:
        logging.error(f"打包清理失败: {e}")
        return False


if __name__ == "__main__":
    #csv_path = "/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/objectSelectionOptimized/jobs/jobs_eachYear/UL2018/cluster_logs.csv"

    if not os.path.exists(csv_path):
        logging.error(f"CSV文件不存在: {csv_path}")
    
    while True:
        status_all = process_clusters(csv_path)
        if status_all:
            print("All jobs finished!")
            logging.info("All jobs finished!")
            break
        subprocess.run("sleep 180", shell=True)
    #get_job_status(18570886)