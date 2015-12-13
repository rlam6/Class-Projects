LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
	USE IEEE.STD_LOGIC_ARITH.ALL;
	USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY dma IS
	GENERIC (NBIT : INTEGER := 32;
		 ABIT : INTEGER := 6);
	PORT (clk: IN BIT; 
	      rst: IN STD_LOGIC;
	      request: IN STD_LOGIC;
	      addr: IN STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
	      data_out: OUT STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0);
	      addr_out : OUT STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
	      acknowledge : OUT STD_LOGIC);
END dma;


ARCHITECTURE sequential OF dma IS
	SIGNAL rom_addr : STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0) := (OTHERS => 'X');
COMPONENT rom IS
	GENERIC (ABIT : INTEGER := 6;
		 NBIT : INTEGER := 32);
	PORT (clk: IN BIT; 
	      address: IN STD_LOGIC_VECTOR (ABIT-1 DOWNTO 0);
	      data_out: OUT STD_LOGIC_VECTOR(NBIT-1 DOWNTO 0));
END COMPONENT;
BEGIN
	PROCESS (clk, rst) BEGIN
		IF (rst='0') THEN
			rom_addr <= (OTHERS => 'X');
		ELSIF (clk'EVENT AND clk='0') THEN
			IF (rst='1') THEN
				IF (request='1') THEN
					rom_addr <= addr;
					acknowledge <= '1';
				END IF;
				ELSE
					acknowledge <= '0';
			END IF;
		END IF;
	END PROCESS;
	main_memory : rom PORT MAP (clk, rom_addr, data_out);
	addr_out <= addr;
END ARCHITECTURE;
