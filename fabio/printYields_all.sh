for category in 1tau0L 1tau1e 1tau1mu 1tau2OSL 1tau2SSL 1tau3L 2tau0L 2tau1e 2tau1mu 2tau2OSL 2tau2SSL; do
root -l -q "printYields.cpp(\"${category}\")"
done
