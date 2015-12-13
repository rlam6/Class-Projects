LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
	USE IEEE.STD_LOGIC_ARITH.ALL;
	USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY ram_array IS
	GENERIC (N: integer := 6; M: integer := 32);
	PORT (clk: IN BIT;
	      rst_s, we : IN STD_LOGIC;
	      adr: IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
	      din: IN STD_LOGIC_VECTOR(M-1 DOWNTO 0);
	      dout: OUT STD_LOGIC_VECTOR(M-1 DOWNTO 0));
end;

ARCHITECTURE synth OF ram_array IS
	TYPE mem_array IS array ((2**N-1) DOWNTO 0) OF STD_LOGIC_VECTOR (M-1 DOWNTO 0);
	SIGNAL mem: mem_array;
BEGIN
	PROCESS (clk) BEGIN
		IF clk'EVENT AND clk = '1' THEN
			IF (we = '1' AND rst_s='1') THEN
				mem (CONV_INTEGER(adr)) <= din;
			END IF;
		END IF;
	END PROCESS;
	dout <= mem (CONV_INTEGER(adr));
END;
