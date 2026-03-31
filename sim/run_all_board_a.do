# =============================================================================
# ModelSim script — Run ALL Board A testbenches
#
# Prerequisites:
#   do compile_board_a.do           ;# or do compile_all.do
#
# Usage (from sim/ directory):
#   do run_all_board_a.do
# =============================================================================

set tb_list {
    tb_market_sim
    tb_market_noise_gen
    tb_exchange_lite
    tb_tx_arbiter
    tb_board_a_ctrl
    tb_board_a_top
}

set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Running: $tb"
    puts "==========================================="

    onbreak {resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    if {[catch {
        vsim -voptargs=+acc work.$tb -quiet
        run -all
        quit -sim
    } err]} {
        puts ">>> FAIL: $tb (Tcl error: $err)"
        lappend fail_list $tb
        continue
    }

    set had_fatal 0
    if {[file exists transcript]} {
        set fp [open transcript r]
        seek $fp $fsize
        set new_content [read $fp]
        close $fp
        if {[string first "** Fatal:" $new_content] >= 0 ||
            [string first "** Error:" $new_content] >= 0} {
            set had_fatal 1
        }
    }

    if {$had_fatal} {
        puts ">>> FAIL: $tb"
        lappend fail_list $tb
    } else {
        puts ">>> PASS: $tb"
        lappend pass_list $tb
    }
}

puts "\n==========================================="
puts " Board A Results"
puts "==========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-------------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
}
puts "==========================================="
