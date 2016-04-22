CREATE DATABASE IF NOT EXISTS UCA DEFAULT CHARACTER SET latin1;
USE UCA;

SET FOREIGN_KEY_CHECKS=0;

-- ENTITY SETS
DROP TABLE IF EXISTS airplane;
DROP TABLE IF EXISTS flight;
DROP TABLE IF EXISTS employee;
DROP TABLE IF EXISTS maintenance_engineer;
DROP TABLE IF EXISTS pilot;
DROP TABLE IF EXISTS flight_attendant;
DROP TABLE IF EXISTS operation_staff;
DROP TABLE IF EXISTS lounge;
DROP TABLE IF EXISTS dish;
DROP TABLE IF EXISTS dish_order;
DROP TABLE IF EXISTS customer;
DROP TABLE IF EXISTS credit_card;
DROP TABLE IF EXISTS airport;

-- RELATIONSHIP TABLES
DROP TABLE IF EXISTS maintains;
DROP TABLE IF EXISTS operates;
DROP TABLE IF EXISTS participates;
DROP TABLE IF EXISTS assigned;
DROP TABLE IF EXISTS reserves;
DROP TABLE IF EXISTS `contains`;

SET FOREIGN_KEY_CHECKS=1;


-- ENTITY SETS

-- Table structure for Airport
CREATE TABLE airport (
	`name` VARCHAR(20),
    IATA_code CHAR(3),
    airport_city VARCHAR(20),
    airport_state CHAR(2),
    PRIMARY KEY (IATA_code)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Airplane
CREATE TABLE airplane (
	purchased_year INTEGER,
    model_num CHAR(4),
    manufactured_year INTEGER,
    capacity INTEGER,
    reg_num VARCHAR(20),
    PRIMARY KEY (reg_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Flight
CREATE TABLE flight (
	proj_arrival DATETIME,
    proj_depart DATETIME,
	actual_arrival DATETIME,
    actual_depart DATETIME,
    flight_num VARCHAR(20),
    reg_num VARCHAR(20),
    depart_IATA CHAR(3) NOT NULL,
    arrive_IATA CHAR(3) NOT NULL,
    PRIMARY KEY (proj_depart, flight_num),
    FOREIGN KEY (reg_num) REFERENCES airplane(reg_num),
    FOREIGN KEY (depart_IATA) REFERENCES airport(IATA_code),
    FOREIGN KEY (arrive_IATA) REFERENCES airport(IATA_code)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




-- Table structure for Employee
CREATE TABLE employee (
	eid INTEGER,
	phone_num CHAR(12),
    birth_date DATE,
    job_title VARCHAR(20),
    ssn CHAR(11),
    address_street VARCHAR(20),
    address_state CHAR(2),
    address_city VARCHAR(10),
    address_zip INTEGER,
    PRIMARY KEY (eid)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Maintenance Engineers
CREATE TABLE maintenance_engineer (
	`mid` INTEGER,
    skill VARCHAR(100),
    PRIMARY KEY (`mid`),
    FOREIGN KEY (`mid`) REFERENCES employee(eid)
		ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Pilots
CREATE TABLE pilot (
	pid INTEGER,
    since INTEGER,
    PRIMARY KEY (pid),
    FOREIGN KEY (pid) REFERENCES employee(eid)
		ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Flight Attendants
CREATE TABLE flight_attendant (
	fid INTEGER,
    service_year INTEGER,
    PRIMARY KEY (fid),
    FOREIGN KEY (fid) REFERENCES employee(eid)
		ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Operation Staff
CREATE TABLE operation_staff (
	osid INTEGER,
    department VARCHAR(50),
    PRIMARY KEY (osid),
    FOREIGN KEY (osid) REFERENCES employee(eid)
		ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



-- Table structure for Customer
CREATE TABLE customer (
	cid INTEGER,
    ssn CHAR(11),
    gender CHAR(1),
    `e-mail` VARCHAR(50),
    address_street VARCHAR(20),
    address_state CHAR(2),
    address_city VARCHAR(10),
    address_zip INTEGER,
    PRIMARY KEY (cid)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for credit_card
-- Multi-valued composite attribute for customer
CREATE TABLE credit_card (
	cid INTEGER,
    `number` INTEGER,
    expr_date CHAR(7),
    PRIMARY KEY (cid)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Lounge
CREATE TABLE lounge (
	IATA_code CHAR(3) NOT NULL,
	lounge_location VARCHAR(20),
    lounge_id INTEGER,
    PRIMARY KEY (lounge_id),
    FOREIGN KEY (IATA_code) REFERENCES airport(IATA_code)
		ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Dish
CREATE TABLE dish (
	dish_name VARCHAR(20),
    price DECIMAL(2,2),
    lounge_id INTEGER NOT NULL,
    PRIMARY KEY (dish_name, lounge_id),
    FOREIGN KEY (lounge_id) REFERENCES lounge(lounge_id)
		ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for Dish_order
CREATE TABLE dish_order (
	oid INTEGER,
    order_datetime DATETIME,
    total_amount DECIMAL(6,2),
    lounge_id INTEGER,
    cid INTEGER NOT NULL,
    PRIMARY KEY (oid),
    FOREIGN KEY (lounge_id) REFERENCES lounge(lounge_id),
    FOREIGN KEY (cid) REFERENCES customer(cid)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;





-- RELATIONSHIP TABLES

-- -----(1)----- Thin line = partial participation
-- =====(1)===== Thick line = total participation
-- 1, N, M = cardinality constraints


-- Table structure for "Maintains"
-- Maintenance Engineer ---(M)---  <Maintains>  ---(N)--- Airplane
CREATE TABLE `maintains` (
	`mid` INTEGER,				-- MUST be maintenance engineer
    `reg_num` VARCHAR(20),
    PRIMARY KEY (`mid`, reg_num),
    FOREIGN KEY (`mid`) REFERENCES maintenance_engineer(`mid`),
    FOREIGN KEY (reg_num) REFERENCES airplane(reg_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for "Operates"
-- Pilot ---(M)---  <Operates>  ---(N)--- Flight
CREATE TABLE `operates` (
	`pid` INTEGER, 				-- MUST be a pilot
    `proj_depart` DATETIME,
    `flight_num` VARCHAR(20),
    PRIMARY KEY (`pid`, proj_depart, flight_num),
    FOREIGN KEY (`pid`) REFERENCES pilot(`pid`),
    FOREIGN KEY (proj_depart, flight_num) REFERENCES flight(proj_depart, flight_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Table structure for "Participates"
-- Flight Attendant ---(M)---  <participates>  ---(N)--- Flight
CREATE TABLE `participates` (
	fid INTEGER, 				-- MUST be a flight attendant
    `proj_depart` DATETIME,
    `flight_num` VARCHAR(20),
    PRIMARY KEY (fid, proj_depart, flight_num),
    FOREIGN KEY (fid) REFERENCES flight_attendant(fid),
    FOREIGN KEY (proj_depart, flight_num) REFERENCES flight(proj_depart, flight_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;




-- Table structure for "Reserves"
-- Customer ---(N)---  <reserves>  ---(M)--- Reserves
CREATE TABLE `reserves` (
    `proj_depart` DATETIME,
    `flight_num` VARCHAR(20),
    `cid` INTEGER,
    `purchased_datetime` DATETIME,
    `price` DECIMAL(8,2),
    `quantity` INTEGER,
    PRIMARY KEY (cid, proj_depart, flight_num),
    FOREIGN KEY (cid) REFERENCES customer(cid),
    FOREIGN KEY (proj_depart, flight_num) REFERENCES flight(proj_depart, flight_num)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;





-- Table structure for "Contains"
-- DishOrder ---(N)---  <contains>  ---(M)--- Dish
CREATE TABLE `contains` (
	`dish_name` VARCHAR(20),
    `lounge_id` INTEGER NOT NULL,
    `oid` INTEGER,
    `quantity` INTEGER,
    PRIMARY KEY (dish_name, lounge_id, oid),
    FOREIGN KEY (dish_name, lounge_id) REFERENCES dish(dish_name, lounge_id),
    FOREIGN KEY (oid) REFERENCES dish_order(oid)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
