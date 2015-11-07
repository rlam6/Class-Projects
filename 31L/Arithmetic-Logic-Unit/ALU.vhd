--------------------------Full-Adder (FA) Definition----------------------------
LIBRARY ieee;
	USE ieee.std_logic_1164.ALL;

ENTITY FA IS
	PORT(i0, i1, cin: IN STD_LOGIC; s, cout: OUT STD_LOGIC);
END FA;

ARCHITECTURE FA_Arch OF FA IS
BEGIN
	s <= (NOT i0 AND NOT i1 AND cin) OR
		(NOT i0 AND i1 AND NOT cin) OR
		(i0 AND NOt i1 AND NOT cin) OR
		(i0 AND i1 AND cin);
	
	cout <=	(NOT i0 AND i1 AND cin) OR
			(i0 AND NOT i1 AND cin) OR
			(i0 AND i1 AND NOT cin) OR
			(i0 AND i1 AND cin);
END FA_Arch;

--------------------------Sub w/ BC (subc) Definition----------------------------
LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;

ENTITY subc IS
PORT(a, b, bin: IN STD_LOGIC;
	 y, bout: OUT STD_LOGIC);
END subc;
ARCHITECTURE subc OF subc IS
BEGIN
	y <= (NOT a and (b XOR bin)) or (a and ((b AND bin) or (NOT b and not bin)));
	bout <= (NOT a AND b) OR (NOT a AND bin) OR (b AND bin);
END subc;

---Subtraction (Sub) Definition---
LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
ENTITY sub IS
PORT(a, b: IN STD_LOGIC;
	 y, bout: OUT STD_LOGIC);
END sub;
ARCHITECTURE sub of sub IS
BEGIN
	y <= a XOR b;
	bout <= NOT a AND b;
END sub;

---INCREMENT (increment) DEFINITION---
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY increment IS
	PORT(a, inc, cin: IN STD_LOGIC;
		y, cout: OUT STD_LOGIC);
END;

ARCHITECTURE increment OF increment IS
COMPONENT FA IS
	PORT(i0, i1, cin: IN STD_LOGIC; s, cout: OUT STD_LOGIC);
END COMPONENT;
BEGIN
	comp : FA PORT MAP(a, inc, cin, y, cout);
END;

---DECREMENT (decrement) DEFINITION---
library ieee;
use ieee.std_logic_1164.ALL;
entity decrement is
	port (
	a, dec, bin: in std_logic;
	sum, bout: out std_logic
	);
END decrement;
architecture decrement_arch of decrement is
component subc is
	PORT(a, b, bin: IN STD_LOGIC; y, bout: OUT STD_LOGIC);
end component;
begin
	--sum <= (NOT a AND NOT bin) OR (a AND bin);
	--bout <= (NOT a AND NOT bin) OR (NOT a AND bin) OR (a AND bin);
	comp : subc PORT MAP (a, dec, bin, sum, bout);
end decrement_arch;

---ADD & INCREMENT (add_incr) DEFINITION---
library ieee;
use ieee.std_logic_1164.ALL;
entity add_incr is
	port(
	a: in std_logic;
	b: in std_logic;
	cin: in std_logic;
	y: out std_logic;
	cout: out std_logic
	);
END add_incr;
architecture add_incr_arch of add_incr is
COMPONENT FA IS
	PORT(i0, i1, cin: IN STD_LOGIC; s, cout: OUT STD_LOGIC);
END COMPONENT;
SIGNAL oneBit, zeroBit, temp, temp1 : STD_LOGIC;
begin
	oneBit <= '1';
	zeroBit <= '0';
	comp1 : FA PORT MAP (a, b, zeroBit, temp);
	comp2 : FA PORT MAP (temp, oneBit, cin, y, cout);
end add_incr_arch;

---BITWISE AND (andgate) DEFINITION---
library ieee;
	use ieee.std_logic_1164.ALL;
entity andgate is
	PORT (
	a, b: in std_logic;
	sum: out std_logic
	);
end andgate;

ARCHITECTURE and_arch of andgate is
begin
	sum <= a and b;
end and_arch;
---BITWISE OR (orgate) DEFINITION---
library ieee;
	use ieee.std_logic_1164.ALL;
entity orgate is
	Port(
	a, b: in std_logic;
	sum: out std_logic
	);
end orgate;

architecture orgate_arch of orgate is
begin
	sum <= a or b;
end orgate_arch;

---BITWISE XOR (xorgate) DEFINITION---
library ieee;
	use ieee.std_logic_1164.ALL;
entity xorgate is
	Port(
	a, b: in std_logic;
	sum: out std_logic
	);
end xorgate;

architecture xorgate_arch of xorgate is
begin
	sum <= a xor b;
end xorgate_arch;

---MOVE (move) DEFINITION---
library ieee;
use ieee.std_logic_1164.ALL;
entity move is
	port (
	a: in std_logic;
	sum: out std_logic
	);
end move;
architecture move_arch of move is
begin
	sum <= a;
end move_arch;

---COMPLIMENT (compliment) DEFINITION---
library ieee;
use ieee.std_logic_1164.ALL;
entity compliment is
	port (
	a: in std_logic;
	sum: out std_logic
	);
end compliment;
architecture compliment_arch of compliment is
signal aNot : STD_LOGIC;
begin
	aNot <= not a;
	sum <= aNot;
end compliment_arch;

---ONE BIT SHIFT LEFT (bitSHL) DEFINITION---
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY bitSHL IS
	PORT(a, cin: IN STD_LOGIC;
		y, cout: OUT STD_LOGIC);
END bitSHL;

ARCHITECTURE bitSHL OF bitSHL IS
BEGIN
	y <= cin;
	cout <= a;
END bitSHL;

---4BitMUX (mux41) Definition---
library IEEE;
  use IEEE.STD_LOGIC_1164.ALL;

entity mux41 is
  port (
    D3, D2, D1, D0  : in std_logic;
    A1, A0 : in std_logic;
    Y      : out std_logic
  );
end mux41;

architecture DataFlow of mux41 is
  signal m0, m1, m2, m3 : std_logic;
begin  -- mux41
  m3 <= (not A1 and not A0 and D0);
  m2 <= (not A1 and A0 and D1);
  m1 <= (A1 and not A0 and D2);
  m0 <= (A1 and A0 and D3);

  Y <= m3 or m2 or m1 or m0;
end DataFlow;

---8BITMUX (mux8x1) DEFINITION---
library IEEE;
  use IEEE.STD_LOGIC_1164.ALL;
ENTITY mux8x1 IS
	PORT (	D7, D6, D5, D4, D3, D2, D1, D0 : IN STD_LOGIC;
		A: in STD_LOGIC_VECTOR (2 downto 0);
		Y : OUT STD_LOGIC
		);
end mux8x1;

architecture mux8x1 of mux8x1 is
component mux41 is
	  port (
	    D3, D2, D1, D0  : in std_logic;
	    A1, A0 : in std_logic;
	    Y      : out std_logic
	  );
end component;
SIGNAL F1, F0 : STD_LOGIC;
begin
	component1 : mux41 port map (D7, D6, D5, D4, A(1), A(0), F1);
	component2 : mux41 port map (D3, D2, D1, D0, A(1), A(0), F0);
	componentFINAL : mux41 PORT MAP ('0', '0', F1, F0, '0', A(2), Y);
end mux8x1;

---MAIN CODE---
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.All;

ENTITY ALU_1bit IS

  PORT(
         A : IN STD_LOGIC ;
   	     B : IN STD_LOGIC ;
	   cin : IN STD_LOGIC ;
	 opsel : IN STD_LOGIC_VECTOR (2 DOWNTO 0);
	  mode : IN STD_LOGIC ;
	output1 : OUT STD_LOGIC ;
	  cout : OUT STD_LOGIC
	  );


END ALU_1bit;

ARCHITECTURE ALU_1bit of ALU_1bit IS
---------------------BEGIN COMPONENT DECLARATIONS---------------------
COMPONENT mux8x1 IS
	PORT (	D7, D6, D5, D4, D3, D2, D1, D0 : IN STD_LOGIC;
		A: in STD_LOGIC_VECTOR (2 downto 0);
		Y : OUT STD_LOGIC
		); 
END COMPONENT;
COMPONENT FA IS
	PORT(i0, i1, cin: IN STD_LOGIC; s, cout: OUT STD_LOGIC);
END COMPONENT;
COMPONENT subc IS
	PORT(a, b, bin: IN STD_LOGIC; y, bout: OUT STD_LOGIC);
END COMPONENT;
COMPONENT sub IS
	PORT(a, b: IN STD_LOGIC; y, bout: OUT STD_LOGIC);
END COMPONENT;
COMPONENT increment IS
	PORT(a, inc, cin: IN STD_LOGIC; y, cout: OUT STD_LOGIC);
END COMPONENT;
COMPONENT decrement IS
	PORT (a, dec, bin: IN STD_LOGIC; sum, bout: OUT STD_LOGIC);
END COMPONENT;
COMPONENT add_incr IS
	PORT (a, b, cin: IN STD_LOGIC; y, cout : OUT STD_LOGIC);
END COMPONENT;
COMPONENT orgate IS
	PORT (a, b: in std_logic; sum: out std_logic);
END COMPONENT;
COMPONENT andgate IS
	PORT (a: in std_logic; b: in std_logic; sum: out std_logic);
END COMPONENT;
COMPONENT xorgate IS
	Port(a: in std_logic; b: in std_logic; sum: out std_logic);
END COMPONENT;
COMPONENT move IS
	port (a: in std_logic; sum: out std_logic);
END COMPONENT;
COMPONENT compliment IS
	port (a: in std_logic; sum: out std_logic);
END COMPONENT;
COMPONENT bitSHL IS
	PORT(a, cin: IN STD_LOGIC; y, cout: OUT STD_LOGIC);
END COMPONENT;
---------------------END COMPONENT DECLARATIONS---------------------
---------------------BEGIN SIGNAL DECLARATIONS----------------------
SIGNAL addComp, subcComp, moveComp, subComp : STD_LOGIC;
SIGNAL incComp, decComp, addincrComp : STD_LOGIC;
SIGNAL andComp, orComp, xorComp, complComp, bitSHLComp : STD_LOGIC;
SIGNAL addCOUT, subcCOUT, incCOUT, decCOUT, addincrCOUT : STD_LOGIC;
SIGNAL bitSHLCOUT, subCOUT : STD_LOGIC;
SIGNAL dontCare, sel1, sel0, cout1, cout0 : STD_LOGIC;
SIGNAL oneBit, zeroBit : STD_LOGIC;
---------------------END SIGNAL DECLARATIONS------------------------
BEGIN
	dontCare <= 'X'; oneBit <= '1'; zeroBit <= '0';
	-------------SELECT PORT INPUTS--------------------
	add      : FA PORT MAP (A, B, CIN, addComp, addCOUT);
	subBC    : subc PORT MAP (A, B, CIN, subcComp, subcCOUT);
	subtract : sub PORT MAP (A, B, subComp, subCOUT);
	incr     : increment PORT MAP (A, B, CIN, incComp, incCOUT);
	decr     : decrement PORT MAP (A, B, CIN, decComp, decCOUT);
	addincr  : add_incr PORT MAP (A, B, CIN, addincrComp, addincrCOUT);
	orG      : orgate PORT MAP (A, B, orComp);
	andG     : andgate PORT MAP (A, B, andComp);
	xorG     : xorgate PORT MAP (A, B, xorComp);
	moveG    : move PORT MAP (A, moveComp);
	compG    : compliment PORT MAP (A, complComp);
	SHL      : bitSHL PORT MAP (A, CIN, bitSHLComp, bitSHLCOUT);

	-------------OUTPUTS SELECTIONS----------------------------------
	MUX81A : mux8x1 PORT MAP (dontCare, addIncrComp, decComp, incComp,
				subComp, moveComp, subcComp, addComp, 
				opsel, sel0);
	MUX81B : mux8x1 PORT MAP (dontCare, dontCare, bitSHLComp, dontCare,
				complComp, xorComp, orComp, andComp, 
				opsel, sel1);

	-------------COUT SELECTIONS--------------------------------------
	MUX81C : mux8x1 PORT MAP (dontCare, addincrCOUT, decCOUT, incCOUT,
				subCOUT, dontCare, subcCOUT, addCOUT,
				opsel, cout0);
	MUX81D : mux8x1 PORT MAP (dontCare, dontCare, bitSHLCOUT, dontCare,
				dontCare, dontCare, decCOUT, incCOUT,
				opsel, cout1);

	-------------OUTPUTS---------------------
	output1 <= sel1 WHEN mode='1' ELSE sel0;
	cout    <= cout1 WHEN mode='1' ELSE cout0;
END ALU_1bit;

------------------32 BIT ALU----------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.All;

ENTITY ALU IS
  PORT(
         A       : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
   	 B       : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	 CIN	 : IN STD_LOGIC ;
	 opsel   : IN STD_LOGIC_VECTOR (2 DOWNTO 0);
	 mode    : IN STD_LOGIC ;
	 output1 : OUT STD_LOGIC_VECTOR (31 DOWNTO 0) ;
	 cout    : OUT STD_LOGIC
	  );
END ALU;
ARCHITECTURE ALU of ALU IS
COMPONENT ALU_1bit IS
  PORT(
         A : IN STD_LOGIC ;
   	     B : IN STD_LOGIC ;
	   cin : IN STD_LOGIC ;
	 opsel : IN STD_LOGIC_VECTOR (2 DOWNTO 0);
	  mode : IN STD_LOGIC ;
	output1 : OUT STD_LOGIC ;
	  cout : OUT STD_LOGIC
	  );
END COMPONENT;
SIGNAL oneBit : STD_LOGIC;
SIGNAL tempCout: STD_LOGIC;
SIGNAL bFix : STD_LOGIC_VECTOR (31 DOWNTO 0);
BEGIN
  bFix <= (0 => '1', OTHERS => '0') WHEN ((opsel="100" OR opsel="101") AND mode='0') ELSE B;
  tempCout <= cin;
  G1: FOR i IN 0 TO 31 GENERATE
    ALUAssign : ALU_1bit PORT MAP (A(i), bFix(i), tempCout, opsel, mode,
				output1(i), tempCout);
    tempCout <= cin;
  END GENERATE;
  cout <= cin;
END ALU;
