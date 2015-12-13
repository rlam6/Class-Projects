LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
PACKAGE my_components IS
	-----counter: ------
	COMPONENT counter IS
		GENERIC(NBIT: INTEGER := 32;
			STEP: INTEGER := 1);
		PORT (  clk : IN BIT;
		 	rst : IN STD_LOGIC; --synchronous reset
			din : IN STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
			preLoad : IN STD_LOGIC; -- read din if '1'
			asc : IN STD_LOGIC; -- ascending ('0' = descending)
			dout : OUT STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0));
	END COMPONENT;
	-----ALU: ----------
	COMPONENT ALU IS
		GENERIC(NBIT: INTEGER := 32);
		PORT (SIGNAL A, B : IN STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
		      SIGNAL R    : IN STD_LOGIC;
		      SIGNAL FUNCT : STD_LOGIC_VECTOR (3 DOWNTO 0);
		      SIGNAL OUTPUT : OUT STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
		      SIGNAL COUT, EQUAL, OVERFLOW : OUT STD_LOGIC
			);
	END COMPONENT;
	-----sign ext 32 bit: ----------
	COMPONENT sign_ext32 IS
		GENERIC(NBIT: INTEGER := 15);
		PORT (  din : IN STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0);
			dout: OUT STD_LOGIC_VECTOR (31 DOWNTO 0));
	END COMPONENT;
	-----RAM: ----------
	COMPONENT ram_array IS
		GENERIC (N: integer := 6; M: integer := 32);
		PORT (clk: IN BIT;
		      rst_s, we : IN STD_LOGIC;
		      adr: IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
		      din: IN STD_LOGIC_VECTOR(M-1 DOWNTO 0);
		      dout: OUT STD_LOGIC_VECTOR(M-1 DOWNTO 0));
	END COMPONENT;
	-----ROM: ----------
	COMPONENT rom IS
		GENERIC (ABIT : INTEGER := 6;
			 NBIT : INTEGER := 32);
		PORT (clk: IN BIT; 
		      address: IN STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
		      data_out: OUT STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0));
	END COMPONENT;
	-----DMA: ----------
	COMPONENT dma IS
		GENERIC (NBIT : INTEGER := 32;
			 ABIT : INTEGER := 6);
		PORT (clk: IN BIT; 
		      rst: IN STD_LOGIC;
		      request: IN STD_LOGIC;
		      addr: IN STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
		      data_out: OUT STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0);
		      addr_out : OUT STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
	      	      acknowledge : OUT STD_LOGIC);
	END COMPONENT;
	-----Controller: ----------
	COMPONENT controller IS
		PORT(instruction: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
		     RI : OUT STD_LOGIC;
		     rs : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
		     rd : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
		     funct : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
		     rt : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
		     imm : OUT STD_LOGIC_VECTOR (14 DOWNTO 0));
	END COMPONENT;
	-----REGFILE: ----------
	COMPONENT regfile IS
		GENERIC (NBIT: INTEGER := 32;NSEL: INTEGER := 3);
		PORT (clk :IN BIT;
		    rst_s : IN std_logic; -- synchronous reset
		    we : IN std_logic; -- write enable
		    raddr_1 : IN std_logic_vector(NSEL -1 DOWNTO 0); -- read address 1
		    raddr_2 : IN std_logic_vector(NSEL -1 DOWNTO 0); -- read address 2
		    waddr : IN std_logic_vector(NSEL -1 DOWNTO 0); -- write addressr
		    rdata_1 : OUT std_logic_vector(NBIT -1 DOWNTO 0); -- read data 1
		    rdata_2 : OUT std_logic_vector(NBIT -1 DOWNTO 0); -- read data 2
		    wdata : IN std_logic_vector(NBIT -1 DOWNTO 0)); 
	END COMPONENT;
	-----MUX 2-TO-1: ----------
	COMPONENT mux21 IS
		GENERIC (NBIT : INTEGER := 32);
		PORT (	clk : IN BIT;
			D1, D0 : IN STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
			S: IN STD_LOGIC;
			Y : OUT STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0));
	END COMPONENT;
END my_components;
