# tb/_xsim_runner.tcl
# Inner xsim batch runner. Runs simulation for up to 5 ms of sim-time, then
# quits. If the testbench calls $finish before the limit, xsim exits naturally
# and this script is never reached.
run 5ms
puts "\[XSIM_TIMEOUT\] simulation reached 5ms cap without \$finish"
quit
