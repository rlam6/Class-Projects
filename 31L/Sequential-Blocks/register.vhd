------------------reg----------------------
LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
	USE IEEE.STD_LOGIC_UNSIGNED.ALL;
ENTITY regstr IS 
	GENERIC (NBIT: INTEGER := 32;
		 STEP: INTEGER := 1);
	PORT (      clk :      IN BIT;
		    rst_a :    IN STD_LOGIC;
		    rst_s :    IN STD_LOGIC;
		    inc :      IN STD_LOGIC;
		    we :       IN STD_LOGIC;
		    inp :      IN STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0);
		    datadout : OUT STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0)
		);
END ENTITY;
ARCHITECTURE reg OF regstr IS
SIGNAL output : STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0);
BEGIN
	    PROCESS(clk, rst_a)
	    BEGIN
		IF(rst_a = '1') THEN
		    output <= (OTHERS => '0');
		ELSIF (clk'EVENT AND clk = '1') THEN
		    IF (rst_s = '1') THEN
			output <= (OTHERS => '0');
		    ELSIF(inc= '1') THEN
		        output <= output + STEP;
		    ELSIF(we = '1') THEN
		        output <= inp;
		    END IF;
		END IF;
	    END PROCESS;
	    datadout <= output;
END ARCHITECTURE;
