--------------------------Hamming-Encoder------------------------
LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;
-----------------------------------------------------------------
ENTITY HE IS
	PORT(DIN: IN STD_LOGIC_VECTOR (1 TO 11); 
	     DOUT: OUT STD_LOGIC_VECTOR(1 TO 15));
END HE;
-----------------------------------------------------------------
ARCHITECTURE HE OF HE IS
SIGNAL P1, P2, P3 ,P4 : STD_LOGIC;
BEGIN
	P1 <= DIN(1) XOR DIN(2) XOR DIN(4) XOR DIN(5) XOR DIN(7) XOR DIN(9) XOR DIN(11);
	P2 <= DIN(1) XOR DIN(3) XOR DIN(4) XOR DIN(6) XOR DIN(7) XOR DIN(10) XOR DIN(11);
	P3 <= DIN(2) XOR DIN(3) XOR DIN(4) XOR DIN(8) XOR DIN(9) XOR DIN(10) XOR DIN(11);
	P4 <= DIN(5) XOR DIN(6) XOR DIN(7) XOR DIN(8) XOR DIN(9) XOR DIN(10) XOR DIN(11);
	
	DOUT <= P1 & P2 & DIN(1) & P3 & DIN(2 TO 4) & P4 & DIN(5 TO 11);
END HE;
