# =============================================================================
# ModelSim script — Compile + run ALL Shared + Link testbenches
#
# Usage (from sim/ directory):
#   do run_all_shared.do
#
# Self-contained: compiles the shared/link RTL + testbenches, then runs each
# TB and prints a regression summary. Use this when you want to validate just
# the shared/link layer without touching Board A / Board B.
# =============================================================================

# ── Compile only what this group needs ───────────────────────────────────────
do compile_shared.do

# ── Testbench list ───────────────────────────────────────────────────────────
set tb_list {
    tb_debounce
    tb_sync_fifo
    tb_lfsr32
    tb_link_tx
    tb_link_rx
    tb_link_loopback
}

# ── Robust PASS/FAIL detection (matches run_all.do) ──────────────────────────
# Each TB is expected to print one of these explicit success markers:
#   "<tb>: PASS (N checks passed)"
#   "ALL TESTS PASSED"
#   "PASSED: N" + "FAILED: 0"
# Hard-failure markers we look for:
#   "** Fatal:"   "TESTBENCH FAILED"   "Assertion error"
# We deliberately do NOT match bare "FAIL" / "Errors:" — those false-positive
# on ModelSim's clean-exit "Errors: 0" line and on Tcl's own ">>> FAIL:"
# output (which would otherwise mark every TB as failed).

set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Shared + Link — $tb"
    puts "==========================================="

    onbreak {resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    # -voptargs="+acc" — required on ModelSim ASE 2020 (-novopt is
    # deprecated and produces "Error loading design"). Shared/Link
    # modules are small so vopt time is negligible here.
    if {[catch {
        vsim -voptargs="+acc" work.$tb -quiet -onfinish stop
        run -all
        quit -sim
    } err]} {
        puts ">>> FAIL: $tb (Tcl error: $err)"
        lappend fail_list $tb
        catch {quit -sim}
        continue
    }

    set had_fatal 0
    set saw_pass  0
    if {[file exists transcript]} {
        after 200
        set fp [open transcript r]
        seek $fp $fsize
        set new_content [read $fp]
        close $fp

        foreach pat {"** Fatal:" "TESTBENCH FAILED" "Assertion error"} {
            if {[string first $pat $new_content] >= 0} {
                set had_fatal 1
                break
            }
        }
        if {!$had_fatal} {
            if {[string first ": PASS ("        $new_content] >= 0 ||
                [string first "ALL TESTS PASSED" $new_content] >= 0 ||
                ([string first "FAILED: 0" $new_content] >= 0 &&
                 [string first "PASSED:"   $new_content] >= 0)} {
                set saw_pass 1
            }
        }
    }

    if {$had_fatal || !$saw_pass} {
        puts ">>> FAIL: $tb"
        lappend fail_list $tb
    } else {
        puts ">>> PASS: $tb"
        lappend pass_list $tb
    }
}

# ── Summary ──────────────────────────────────────────────────────────────────
puts "\n==========================================="
puts " SHARED + LINK SUMMARY"
puts "==========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-------------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
} else {
    puts " ALL $total TESTBENCHES PASSED"
}
puts "==========================================="
