LIBRARY ieee;
	USE ieee.std_logic_1164.all;
	USE ieee.numeric_std.all;

ENTITY regfile IS 
	GENERIC (NBIT: INTEGER := 32;NSEL: INTEGER := 6);
	PORT (clk :IN BIT;
	    rst_s : IN std_logic; -- synchronous reset
	    we : IN std_logic; -- write enable
	    raddr_1 : IN std_logic_vector(NSEL-1 DOWNTO 0); -- read address 1
	    raddr_2 : IN std_logic_vector(NSEL-1 DOWNTO 0); -- read address 2
	    waddr : IN std_logic_vector(NSEL -1 DOWNTO 0); -- write addressr
	    rdata_1 : OUT std_logic_vector(NBIT -1 DOWNTO 0); -- read data 1
	    rdata_2 : OUT std_logic_vector(NBIT -1 DOWNTO 0); -- read data 2
	    wdata : IN std_logic_vector(NBIT -1 DOWNTO 0)); 
END regfile;

ARCHITECTURE registerfile OF regfile IS
    SUBTYPE vect IS STD_LOGIC_VECTOR(NBIT - 1 DOWNTO 0);
    TYPE matrix IS ARRAY(2**NSEL-1 DOWNTO 0) OF vect;
    SIGNAL row: matrix;
        SIGNAL temp_r1, temp_r2, temp_w: UNSIGNED (NSEL-1 DOWNTO 0);
	SIGNAL ind_r1, ind_r2, ind_w: INTEGER;
BEGIN
	-------Get unsigned vector for address--------
	temp_r1 <= UNSIGNED(raddr_1);
	temp_r2 <= UNSIGNED(raddr_2);
	temp_w <= UNSIGNED(waddr);

	-------Convert unsigned address to int--------
	ind_r1 <= to_integer(temp_r1);
	ind_r2 <= to_integer(temp_r2);
	ind_w <= to_integer(temp_w);

	PROCESS(clk, rst_s)
	BEGIN
		IF (rst_s = '1') THEN
			L2: FOR i IN 2**NSEL-1 DOWNTO 0 LOOP
				row(i) <= (OTHERS => '0');
			END LOOP;
		ELSIF(clk'EVENT AND clk='0') THEN
			IF(we = '1') THEN
				row(ind_w) <= wdata;
			END IF;
		END IF;
	END PROCESS;
	rdata_1 <= row(ind_r1) when clk='1';
	rdata_2 <= row(ind_r2) when clk='1';
END ARCHITECTURE;
