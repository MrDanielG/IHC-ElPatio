-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Tipo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Tipo` (
  `id_tipo` INT NOT NULL,
  `nombre_tipo` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_tipo`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Usuario`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Usuario` (
  `clave` INT NOT NULL,
  `apellido_paterno` VARCHAR(45) NOT NULL,
  `apellido_materno` VARCHAR(45) NOT NULL,
  `nombre` VARCHAR(45) NOT NULL,
  `Tipo_id_tipo` INT NOT NULL,
  PRIMARY KEY (`clave`),
  INDEX `fk_Usuario_Tipo_idx` (`Tipo_id_tipo` ASC),
  CONSTRAINT `fk_Usuario_Tipo`
    FOREIGN KEY (`Tipo_id_tipo`)
    REFERENCES `mydb`.`Tipo` (`id_tipo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Mesa`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Mesa` (
  `numero_mesa` INT NOT NULL,
  `estado` VARCHAR(15) NOT NULL,
  PRIMARY KEY (`numero_mesa`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Comanda`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Comanda` (
  `id_comanda` VARCHAR(45) NOT NULL,
  `hora_apertura` DATETIME NOT NULL,
  `numero_personas` INT NOT NULL,
  `Usuario_clave` INT NOT NULL,
  `Mesa_numero_mesa` INT NOT NULL,
  PRIMARY KEY (`id_comanda`),
  INDEX `fk_Comanda_Usuario1_idx` (`Usuario_clave` ASC),
  INDEX `fk_Comanda_Mesa1_idx` (`Mesa_numero_mesa` ASC),
  CONSTRAINT `fk_Comanda_Usuario1`
    FOREIGN KEY (`Usuario_clave`)
    REFERENCES `mydb`.`Usuario` (`clave`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Comanda_Mesa1`
    FOREIGN KEY (`Mesa_numero_mesa`)
    REFERENCES `mydb`.`Mesa` (`numero_mesa`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Platillo`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Platillo` (
  `id_platillo` INT NOT NULL,
  `precio` DOUBLE NOT NULL,
  `nombre` VARCHAR(45) NOT NULL,
  `categoria` VARCHAR(45) NOT NULL,
  `estado` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_platillo`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Pedido`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Pedido` (
  `comentario` VARCHAR(45) NOT NULL,
  `Platillo_id_platillo` INT NOT NULL,
  `Comanda_id_comanda` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`comentario`),
  INDEX `fk_Pedido_Platillo1_idx` (`Platillo_id_platillo` ASC),
  INDEX `fk_Pedido_Comanda1_idx` (`Comanda_id_comanda` ASC),
  CONSTRAINT `fk_Pedido_Platillo1`
    FOREIGN KEY (`Platillo_id_platillo`)
    REFERENCES `mydb`.`Platillo` (`id_platillo`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Pedido_Comanda1`
    FOREIGN KEY (`Comanda_id_comanda`)
    REFERENCES `mydb`.`Comanda` (`id_comanda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Ticket`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Ticket` (
  `id_ticket` INT NOT NULL,
  `fecha` DATETIME NOT NULL,
  `hora` DATETIME NOT NULL,
  `iva` FLOAT NOT NULL,
  `metodo` VARCHAR(45) NOT NULL,
  `total` DOUBLE NOT NULL,
  `Comanda_id_comanda` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_ticket`),
  INDEX `fk_Ticket_Comanda1_idx` (`Comanda_id_comanda` ASC),
  CONSTRAINT `fk_Ticket_Comanda1`
    FOREIGN KEY (`Comanda_id_comanda`)
    REFERENCES `mydb`.`Comanda` (`id_comanda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
