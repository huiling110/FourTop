
# XGBOOST_LIB=-L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/lib64/ -lxgboost
# XGBOOST_FLAGS = -I/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/include
XGBOOST_LIB=-L/cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/lib/ -lxgboost

RABIT_INA=-I/cvmfs/cms.cern.ch/$SCRAM_ARCH/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/rabit/include/


CC=g++
CFLAGS=-g $(RABIT_INA) 
LDFLAGS=$(XGBOOST_FLAGS)



main: test.o
	$(CC) $(LDFLAGS) -o $@ $^

test.o: test.C
    $(CC)  $(CFLAGS) -c -o 


clean:
    rm -rf main test.o



