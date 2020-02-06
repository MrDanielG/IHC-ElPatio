-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 29-01-2020 a las 08:21:24
-- Versión del servidor: 10.4.11-MariaDB
-- Versión de PHP: 7.2.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `el_patio`
--
CREATE DATABASE IF NOT EXISTS `el_patio` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `el_patio`;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `comanda`
--

DROP TABLE IF EXISTS `comanda`;
CREATE TABLE `comanda` (
  `id_comanda` int(11) NOT NULL,
  `hora_apertura` datetime NOT NULL,
  `numero_personas` int(11) NOT NULL,
  `Usuario_clave` int(11) NOT NULL,
  `Mesa_numero_mesa` int(11) NOT NULL,
  `estado` varchar(11) NOT NULL DEFAULT 'Abierta',
  `comentario` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mesa`
--

DROP TABLE IF EXISTS `mesa`;
CREATE TABLE `mesa` (
  `numero_mesa` int(11) NOT NULL,
  `estado` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `pedido`
--

DROP TABLE IF EXISTS `pedido`;
CREATE TABLE `pedido` (
  `id_Pedido` int(11) NOT NULL,
  `comentario` varchar(45) NOT NULL,
  `Comanda_id_comanda` int(11) NOT NULL,
  `Platillo_id_platillo` int(11) NOT NULL,
  `estado` varchar(15) NOT NULL DEFAULT 'En proceso'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `platillo`
--

DROP TABLE IF EXISTS `platillo`;
CREATE TABLE `platillo` (
  `id_platillo` int(11) NOT NULL,
  `precio` double NOT NULL,
  `nombre` varchar(45) NOT NULL,
  `categoria` varchar(45) NOT NULL,
  `estado` varchar(45) NOT NULL,
  `foto` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `platillo`
--

INSERT INTO `platillo` (`id_platillo`, `precio`, `nombre`, `categoria`, `estado`, `foto`) VALUES
(1, 84, 'Con jamón, tocino, salchicha ó longaniza', 'Huevos', 'disponible', ''),
(2, 84, 'Al albañil', 'Huevos', 'disponible', ''),
(3, 84, 'A la mexicana', 'Huevos', 'disponible', ''),
(4, 84, 'Tirados', 'Huevos', 'disponible', ''),
(5, 97, 'Longaniza en salsa roja', 'Con Hambre', 'disponibles', ''),
(6, 97, 'Puntas de filete a la mexicana', 'Con Hambre', 'disponibles', ''),
(7, 97, 'Chicharrón en salsa verde', 'Con Hambre', 'disponibles', ''),
(8, 97, 'Chilaquiles rojos', 'Con Hambre', 'disponibles', ''),
(9, 75, 'Tlacoyos', 'Del Comal', 'disponibles', ''),
(10, 75, 'Quesadilla natural', 'Del Comal', 'disponibles', ''),
(11, 75, 'Trilogía de picaditas', 'Del Comal', 'disponibles', ''),
(12, 75, 'Memela tradicional', 'Del Comal', 'disponibles', ''),
(13, 75, 'Gorditas jarochas', 'Del Comal', 'disponibles', ''),
(14, 79, 'Huevos rancheros', 'La Carta', 'disponibles', ''),
(15, 97, 'Huevos con machaca', 'La Carta', 'disponibles', ''),
(16, 89, 'Huevos achichcarrados', 'La Carta', 'disponibles', ''),
(17, 70, 'Costra especial \"El Patio\"', 'La Carta', 'disponibles', ''),
(18, 120, 'Huevos al caballo', 'La Carta', 'disponibles', ''),
(19, 86, 'Huevos en cazuela con jocoque', 'La Carta', 'disponibles', ''),
(20, 89, 'Huevos del mercado', 'La Carta', 'disponibles', ''),
(21, 81, 'Omelette', 'La Carta', 'disponibles', ''),
(22, 97, 'Omelette poblano', 'La Carta', 'disponibles', ''),
(23, 89, 'Enchiladas', 'La Carta', 'disponibles', ''),
(24, 99, 'Enchiladas suizas', 'La Carta', 'disponibles', ''),
(25, 85, 'Enfrijoladas \"El Patio\"', 'La Carta', 'disponibles', ''),
(26, 119, 'Cecina', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(27, 99, 'Tacos de cecina', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(28, 79, 'Huevos motuleños', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(29, 53, 'Plato de fruta', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(30, 46, 'Ensalada de manzana', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(31, 71, 'Hot cakes (3 pzas.)', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(32, 15, 'Pan de dulce (de la casa)', 'La Carta', 'disponibles', '../fotos_menu/huevos.jpg'),
(33, 25, 'Americano', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(34, 31, 'Expresso', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(35, 32, 'Capuccino', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(36, 35, 'Lechero', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(37, 23, 'Té', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(38, 33, 'Chocolate', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(39, 25, 'Vaso leche chico', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(40, 30, 'Vaso leche grande', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(41, 35, 'Latte', 'Bebidas calientes', 'disponibles', '../fotos_menu/huevos.jpg'),
(42, 39, 'Malteadas fresa', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(43, 39, 'Malteadas vainilla', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(44, 39, 'Malteadas chocolate', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(45, 49, 'Ichi-koi moka oreo', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(46, 49, 'Ichi-koi chips ahoy', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(47, 49, 'Ichi-koi clásico', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(48, 33, 'Chocomilk', 'Bebidas frias', 'disponibles', '../fotos_menu/huevos.jpg'),
(49, 29, 'Vampiro chico(275 ml)', 'Bebidas Jugos', 'disponibles', '../fotos_menu/huevos.jpg'),
(50, 37, 'Vampiro grande(465 ml)', 'Bebidas Jugos', 'disponibles', '../fotos_menu/huevos.jpg'),
(51, 29, 'Oasis chico(275 ml)', 'Bebidas Jugos', 'disponibles', '../fotos_menu/huevos.jpg'),
(52, 37, 'Oasis grande(465 ml)', 'Bebidas Jugos', 'disponibles', '../fotos_menu/huevos.jpg'),
(53, 29, 'Verde chico(275 ml)', 'Bebidas Jugos', 'disponibles', '../fotos_menu/huevos.jpg'),
(54, 37, 'Verde grande(465 ml)', 'Bebidas Jugos', 'disponibles', '../fotos_menu/huevos.jpg'),
(55, 31, 'Cerveza', 'Bebidas Pal Alma', 'disponibles', '../fotos_menu/huevos.jpg'),
(56, 39, 'Michelada', 'Bebidas Pal Alma', 'disponibles', '../fotos_menu/huevos.jpg'),
(57, 47, 'Chelada', 'Bebidas Pal Alma', 'disponibles', '../fotos_menu/huevos.jpg'),
(58, 28, 'Refresco', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(59, 32, 'Agua mineral', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(60, 20, 'Agua embotellada', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(61, 35, 'Soda italiana', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(62, 32, 'Rusa', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(63, 30, 'Limonada', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(64, 30, 'Naranjada', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(65, 42, 'Agua de fresa con avena', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(66, 35, 'Lemon stick', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(67, 35, 'Conga', 'Bebidas Las Que Refrescan', 'disponibles', '../fotos_menu/huevos.jpg'),
(68, 97, 'Chicharrón en salsa roja', 'Con Hambre', 'disponible', ''),
(69, 97, 'Chilaquiles verdes', 'Con Hambre', 'disponible', '');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `ticket`
--

DROP TABLE IF EXISTS `ticket`;
CREATE TABLE `ticket` (
  `id_ticket` int(11) NOT NULL,
  `fecha` datetime NOT NULL,
  `hora` datetime NOT NULL,
  `iva` float NOT NULL,
  `metodo` varchar(45) NOT NULL,
  `total` double NOT NULL,
  `Comanda_id_comanda` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `tipo`
--

DROP TABLE IF EXISTS `tipo`;
CREATE TABLE `tipo` (
  `id_tipo` int(11) NOT NULL,
  `nombre_tipo` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `tipo`
--

INSERT INTO `tipo` (`id_tipo`, `nombre_tipo`) VALUES
(1, 'Administrador'),
(2, 'Mesero'),
(3, 'Cocinero'),
(4, 'Barista'),
(5, 'Almacenista');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuario`
--

DROP TABLE IF EXISTS `usuario`;
CREATE TABLE `usuario` (
  `clave` int(11) NOT NULL,
  `apellido_paterno` varchar(45) NOT NULL,
  `apellido_materno` varchar(45) NOT NULL,
  `nombre` varchar(45) NOT NULL,
  `Tipo_id_tipo` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `comanda`
--
ALTER TABLE `comanda`
  ADD PRIMARY KEY (`id_comanda`),
  ADD KEY `fk_Comanda_Usuario1_idx` (`Usuario_clave`),
  ADD KEY `fk_Comanda_Mesa1_idx` (`Mesa_numero_mesa`);

--
-- Indices de la tabla `mesa`
--
ALTER TABLE `mesa`
  ADD PRIMARY KEY (`numero_mesa`);

--
-- Indices de la tabla `pedido`
--
ALTER TABLE `pedido`
  ADD PRIMARY KEY (`id_Pedido`),
  ADD KEY `fk_Pedido_Comanda1_idx` (`Comanda_id_comanda`),
  ADD KEY `fk_Pedido_Platillo1_idx` (`Platillo_id_platillo`);

--
-- Indices de la tabla `platillo`
--
ALTER TABLE `platillo`
  ADD PRIMARY KEY (`id_platillo`);

--
-- Indices de la tabla `ticket`
--
ALTER TABLE `ticket`
  ADD PRIMARY KEY (`id_ticket`),
  ADD KEY `fk_Ticket_Comanda1_idx` (`Comanda_id_comanda`);

--
-- Indices de la tabla `tipo`
--
ALTER TABLE `tipo`
  ADD PRIMARY KEY (`id_tipo`);

--
-- Indices de la tabla `usuario`
--
ALTER TABLE `usuario`
  ADD PRIMARY KEY (`clave`),
  ADD KEY `fk_Usuario_Tipo_idx` (`Tipo_id_tipo`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `comanda`
--
ALTER TABLE `comanda`
  MODIFY `id_comanda` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `mesa`
--
ALTER TABLE `mesa`
  MODIFY `numero_mesa` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `pedido`
--
ALTER TABLE `pedido`
  MODIFY `id_Pedido` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `platillo`
--
ALTER TABLE `platillo`
  MODIFY `id_platillo` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=112;

--
-- AUTO_INCREMENT de la tabla `ticket`
--
ALTER TABLE `ticket`
  MODIFY `id_ticket` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `tipo`
--
ALTER TABLE `tipo`
  MODIFY `id_tipo` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT de la tabla `usuario`
--
ALTER TABLE `usuario`
  MODIFY `clave` int(11) NOT NULL AUTO_INCREMENT;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `comanda`
--
ALTER TABLE `comanda`
  ADD CONSTRAINT `fk_Comanda_Mesa1` FOREIGN KEY (`Mesa_numero_mesa`) REFERENCES `mesa` (`numero_mesa`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_Comanda_Usuario1` FOREIGN KEY (`Usuario_clave`) REFERENCES `usuario` (`clave`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `pedido`
--
ALTER TABLE `pedido`
  ADD CONSTRAINT `fk_Pedido_Comanda1` FOREIGN KEY (`Comanda_id_comanda`) REFERENCES `comanda` (`id_comanda`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_Pedido_Platillo1` FOREIGN KEY (`Platillo_id_platillo`) REFERENCES `platillo` (`id_platillo`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `ticket`
--
ALTER TABLE `ticket`
  ADD CONSTRAINT `fk_Ticket_Comanda1` FOREIGN KEY (`Comanda_id_comanda`) REFERENCES `comanda` (`id_comanda`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `usuario`
--
ALTER TABLE `usuario`
  ADD CONSTRAINT `fk_Usuario_Tipo` FOREIGN KEY (`Tipo_id_tipo`) REFERENCES `tipo` (`id_tipo`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Ocupado');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');
INSERT INTO mesa(estado) values('Libre');



/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
