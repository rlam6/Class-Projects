LIBRARY IEEE;
	USE IEEE.STD_LOGIC_1164.ALL;

ENTITY controller IS
	PORT(instruction: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	     RI : OUT STD_LOGIC;
	     rs : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
	     rd : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
	     funct : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
	     rt : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
	     imm : OUT STD_LOGIC_VECTOR (14 DOWNTO 0));
END ENTITY;

ARCHITECTURE sequential OF controller IS
BEGIN
	RI <= instruction (31);
	rs <= instruction (30 DOWNTO 25);
	rd <= instruction (24 DOWNTO 19);
	funct <= instruction (18 DOWNTO 15);
	rt <= instruction (14 DOWNTO 9);
	imm <= instruction (14 DOWNTO 0);
END ARCHITECTURE;
