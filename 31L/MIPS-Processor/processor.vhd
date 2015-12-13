--ASSUMPTIONS / COMPONENTS NOT FULLY FUNCTIONAL
	-- BIT SHIFT LEFT OPERATOR -- CANNOT SHIFT USING STD LOGIC VECTOR
	-- COMPARE OPERATOR RETURNS NEW STD_LOGIC_VECTOR OF EACH BIT THAT SHOWS IF
	-- 				OP A'S BIT WAS GREATER THAN OP B'S BIT

LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
	USE IEEE.STD_LOGIC_ARITH.ALL;
	USE IEEE.STD_LOGIC_UNSIGNED.ALL;
	USE work.my_components.ALL;

ENTITY processor IS
	GENERIC (ABIT : INTEGER := 6;
		 NBIT : INTEGER := 32);
	PORT(   clk : IN BIT;
		addr : IN STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
		rst, request: IN STD_LOGIC;
		dout : OUT STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
		acknowledge, carry, equal, overflow : OUT STD_LOGIC);
END ENTITY;

ARCHITECTURE structural OF processor IS
	---------------COUNTER SIGNALS--------------------
	SIGNAL read_mem_address : STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
	CONSTANT step : INTEGER := 1;
	CONSTANT din : STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0) := (OTHERS => '0');
	CONSTANT preLoad : STD_LOGIC := '0';
	CONSTANT asc : STD_LOGIC := '1';

	---------------RAM SIGNALS------------------------
	SIGNAL instruction : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
	SIGNAL we : STD_LOGIC;

	---------------DMA SIGNALS------------------------
	SIGNAL dmaOut : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
	SIGNAL write_mem_address : STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
	SIGNAL mem_address : STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);

	---------------CONTROLLER SIGNALS------------------------
	SIGNAL RI : STD_LOGIC;
	SIGNAL rs : STD_LOGIC_VECTOR (5 DOWNTO 0);
	SIGNAL rd : STD_LOGIC_VECTOR (5 DOWNTO 0);
	SIGNAL funct : STD_LOGIC_VECTOR (3 DOWNTO 0);
	SIGNAL rt : STD_LOGIC_VECTOR (5 DOWNTO 0);
	SIGNAL tempImm : STD_LOGIC_VECTOR (14 DOWNTO 0);
	SIGNAL imm : STD_LOGIC_VECTOR (31 DOWNTO 0);

	---------------REGFILE SIGNALS------------------------
	CONSTANT weOn   : STD_LOGIC := '1';
	CONSTANT rstOff : STD_LOGIC := '0';
	SIGNAL reg_data : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);

	---------------ALU SIGNALS----------------------------
	SIGNAL opA : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
	SIGNAL opB : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
	SIGNAL regWE : STD_LOGIC;
	SIGNAL aluOut : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
BEGIN
	PROCESS (clk) BEGIN
		IF (clk'EVENT AND clk='1') THEN
			we <= '0';
		ELSIF (clk'EVENT AND clk='0') THEN
			we <= '1';
		END IF;
	END PROCESS;
	
	---------------------FETCH STAGE-----------------------
	get_read_mem_address : counter GENERIC MAP (ABIT, step)
				  PORT MAP (clk, rst, din, preLoad, asc, read_mem_address);
	get_write_mem_address: dma GENERIC MAP (NBIT, ABIT)
				 PORT MAP (clk, rst, request, addr, dmaOut, write_mem_address, acknowledge);
	mem_address <= read_mem_address WHEN we='0' ELSE write_mem_address WHEN we='1';
	get_instruction : ram_array PORT MAP (clk, rst, we, mem_address, dmaOut, instruction);

	--------------------DECODE STAGE-----------------------
	decode : controller PORT MAP (instruction, RI, rs, rd, funct, rt, tempImm);
	get_reg_data : regfile GENERIC MAP (NBIT, ABIT)
				 PORT MAP (clk, rst, weOn, rs, rt, rd, opA, reg_data, aluOut);
	ext : sign_ext32 PORT MAP (tempImm, imm);
	get_opB : mux21 PORT MAP (clk, reg_data, imm, RI, opB);

	--------------------EXECUTE STAGE----------------------
	execute: ALU PORT MAP (opA, opB, RI, funct, aluOut, carry, equal, overflow);
	dout <= aluOut;


	--------TESTING ALU FUNCTIONALITY (comment out if not testing)-----------
	--test: ALU PORT MAP ((OTHERS => '1'), (0 => '1', OTHERS => '0'), '1', "1001", 
	--		dout, carry, equal, overflow);
END ARCHITECTURE;
