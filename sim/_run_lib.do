# =============================================================================
# Shared helper: run_one_test
#
# Sourced by run_all*.do scripts. Defines `run_one_test <tb>` which:
#   1. Redirects ModelSim's transcript to a per-test log file (run_logs/<tb>.log)
#      so PASS/FAIL scanning is reliable -- no offsets into a shared, buffered
#      transcript file. (The previous "[file size transcript] + seek" approach
#      was unreliable in batch mode because ModelSim buffers transcript writes.)
#   2. Launches vsim with -voptargs="+acc" (required on ModelSim ASE 2020;
#      -novopt is deprecated and causes "Error loading design").
#   3. Closes the transcript so the file is flushed before scan.
#   4. Scans the log for hard-failure markers and positive PASS markers.
#
# Returns "PASS", "FAIL", or "ELAB_FAIL" (string).
# =============================================================================

proc run_one_test {tb} {
    if {![file exists run_logs]} { file mkdir run_logs }
    set log_path [file join run_logs "${tb}.log"]
    if {[file exists $log_path]} { file delete $log_path }

    # Don't let `$finish` -> "Break in Module ..." abort the script.
    onbreak {resume}

    # Capture all transcript output into a fresh per-test file.
    transcript file $log_path

    set vsim_err 0
    set err_msg  ""
    if {[catch {
        vsim -voptargs="+acc" work.$tb -quiet -onfinish stop
        run -all
        quit -sim
    } err]} {
        set vsim_err 1
        set err_msg  $err
        catch {quit -sim}
    }

    # Close (and flush) the per-test log so it's safe to read.
    transcript file ""

    if {$vsim_err} {
        puts ">>> FAIL: $tb (Tcl error: $err_msg) -- log: $log_path"
        return "ELAB_FAIL"
    }

    set log_text ""
    if {[file exists $log_path]} {
        set fp [open $log_path r]
        set log_text [read $fp]
        close $fp
    }

    # Hard-failure markers. Deliberately NOT matching plain "FAIL" or
    # "Errors: N" -- "Errors: 0" prints on every clean exit.
    set had_fatal 0
    foreach pat {"** Fatal:" "TESTBENCH FAILED" "Assertion error"} {
        if {[string first $pat $log_text] >= 0} {
            set had_fatal 1
            break
        }
    }

    # Positive PASS markers. Each TB ends with one of:
    #   "<tb>: PASS (N checks passed)"
    #   "ALL TESTS PASSED"
    #   "PASSED: N" together with "FAILED: 0"
    set saw_pass 0
    if {!$had_fatal} {
        if {[string first ": PASS ("        $log_text] >= 0 ||
            [string first "ALL TESTS PASSED" $log_text] >= 0 ||
            ([string first "FAILED: 0" $log_text] >= 0 &&
             [string first "PASSED:"   $log_text] >= 0)} {
            set saw_pass 1
        }
    }

    if {$had_fatal || !$saw_pass} {
        puts ">>> FAIL: $tb  (log: $log_path)"
        return "FAIL"
    } else {
        puts ">>> PASS: $tb"
        return "PASS"
    }
}
