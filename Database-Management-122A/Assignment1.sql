
CREATE DATABASE IF NOT EXISTS `UCA` DEFAULT CHARACTER SET latin1;
USE `UCA`;

-- Table structure for Airplane
DROP TABLE IF EXISTS `Airplane`;
CREATE TABLE `Airplane` (
	`purchased_year` INTEGER,
    `model_num` CHAR(4),
    `manufactured_year` INTEGER,
    `capacity` INTEGER,
    `reg_num` VARCHAR(20),
    PRIMARY KEY (reg_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Flight
DROP TABLE IF EXISTS `Flight`;
CREATE TABLE `Flight` (
	`proj_arrival` DATETIME,
    `proj_depart` DATETIME,
    `flight_num` VARCHAR(6),
    PRIMARY KEY (proj_depart, flight_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Employee
DROP TABLE IF EXISTS `Employee`;
CREATE TABLE `Employee` (
	`phone_num` CHAR(12),
    `birth_date` DATE,
    `job title` VARCHAR(20),
    
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


