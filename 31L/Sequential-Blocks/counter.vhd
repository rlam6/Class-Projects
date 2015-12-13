-------------------------COUNTER----------------------
LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
	USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY counter IS
	GENERIC(NBIT: INTEGER := 32;
		STEP: INTEGER := 1);
	PORT (  clk : IN BIT;
	 	rst_s : IN STD_LOGIC; --synchronous reset
		din : IN STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
		preLoad : IN STD_LOGIC; -- read din if '1'
		asc : IN STD_LOGIC; -- ascending ('0' = descending)
		dout : OUT STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0));
END ENTITY;
ARCHITECTURE counter OF counter is
	SIGNAL count : STD_LOGIC_VECTOR (NBIT-1 DOWNTO 0);
BEGIN
	PROCESS(clk)
	BEGIN
	  IF (clk'EVENT AND clk = '1') THEN
	  	IF (rst_s = '1') THEN
			count <= (NBIT-1 DOWNTO 0 => '0');
		ELSIF (preLoad = '1') THEN
			count <= din;
		ELSIF (asc = '1') THEN
			count <= count + STEP;
		ELSIF (asc='0') THEN
			count <= count - STEP;
		END IF;
	  END IF;
	END PROCESS;
	dout <= count;
END ARCHITECTURE;
