-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2026 Advanced Micro Devices, Inc. All Rights Reserved.
-- -------------------------------------------------------------------------------
-- This file contains confidential and proprietary information
-- of AMD and is protected under U.S. and international copyright
-- and other intellectual property laws.
--
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- AMD, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND AMD HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) AMD shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or AMD had been advised of the
-- possibility of the same.
--
-- CRITICAL APPLICATIONS
-- AMD products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of AMD products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
--
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
--
-- DO NOT MODIFY THIS FILE.

-- MODULE VLNV: amd.com:blockdesign:system:1.0

-- The following code must appear in the VHDL architecture header.

-- COMP_TAG     ------ Begin cut for COMPONENT Declaration ------
COMPONENT system
  PORT (
    btn : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    sw : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    pmod_ja : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    pmod_ja_valid : IN STD_LOGIC;
    pmod_jb_ready : IN STD_LOGIC;
    led : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    rgb0 : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    rgb1 : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    pmod_ja_ready : OUT STD_LOGIC;
    pmod_jb : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    pmod_jb_valid : OUT STD_LOGIC
  );
END COMPONENT;
-- COMP_TAG_END ------  End cut for COMPONENT Declaration  ------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

-- INST_TAG     ------ Begin cut for INSTANTIATION Template ------
your_instance_name : system
  PORT MAP (
    btn => btn,
    sw => sw,
    pmod_ja => pmod_ja,
    pmod_ja_valid => pmod_ja_valid,
    pmod_jb_ready => pmod_jb_ready,
    led => led,
    rgb0 => rgb0,
    rgb1 => rgb1,
    pmod_ja_ready => pmod_ja_ready,
    pmod_jb => pmod_jb,
    pmod_jb_valid => pmod_jb_valid
  );
-- INST_TAG_END ------  End cut for INSTANTIATION Template  ------

-- You must compile the wrapper file system.vhd when simulating
-- the module, system. When compiling the wrapper file, be sure to
-- reference the VHDL simulation library.
