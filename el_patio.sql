-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 06-02-2020 a las 17:39:58
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

--
-- Truncar tablas antes de insertar `comanda`
--

TRUNCATE TABLE `comanda`;
--
-- Volcado de datos para la tabla `comanda`
--

INSERT INTO `comanda` (`id_comanda`, `hora_apertura`, `numero_personas`, `Usuario_clave`, `Mesa_numero_mesa`, `estado`, `comentario`) VALUES
(1, '2020-02-03 16:35:34', 2, 100, 2, 'Abierta', NULL),
(2, '0000-00-00 00:00:00', 1, 100, 20, 'Abierta', NULL),
(3, '0000-00-00 00:00:00', 1, 100, 7, 'Abierta', NULL),
(4, '0000-00-00 00:00:00', 1, 100, 8, 'Abierta', NULL),
(5, '0000-00-00 00:00:00', 1, 100, 13, 'Abierta', NULL),
(6, '0000-00-00 00:00:00', 1, 100, 6, 'Abierta', NULL),
(7, '0000-00-00 00:00:00', 1, 100, 18, 'Abierta', NULL),
(8, '0000-00-00 00:00:00', 1, 100, 25, 'Abierta', NULL),
(9, '0000-00-00 00:00:00', 1, 100, 19, 'Abierta', NULL),
(10, '0000-00-00 00:00:00', 1, 100, 21, 'Abierta', NULL),
(11, '0000-00-00 00:00:00', 1, 100, 16, 'Abierta', NULL),
(12, '0000-00-00 00:00:00', 1, 100, 24, 'Abierta', NULL),
(13, '0000-00-00 00:00:00', 1, 100, 23, 'Abierta', NULL),
(14, '0000-00-00 00:00:00', 1, 100, 12, 'Abierta', NULL),
(15, '0000-00-00 00:00:00', 1, 100, 9, 'Abierta', NULL),
(16, '0000-00-00 00:00:00', 1, 100, 10, 'Abierta', NULL),
(17, '0000-00-00 00:00:00', 1, 100, 17, 'Abierta', NULL);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `extra`
--

DROP TABLE IF EXISTS `extra`;
CREATE TABLE `extra` (
  `id_extra` int(11) NOT NULL,
  `precio` float NOT NULL,
  `nombre` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `extra`
--

TRUNCATE TABLE `extra`;
-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `ingrediente`
--

DROP TABLE IF EXISTS `ingrediente`;
CREATE TABLE `ingrediente` (
  `id_ingrediente` int(11) NOT NULL,
  `id_insumo` int(11) NOT NULL,
  `fecha_almacenamiento` date NOT NULL,
  `dias_caducidad` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `ingrediente`
--

TRUNCATE TABLE `ingrediente`;
-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `insumo`
--

DROP TABLE IF EXISTS `insumo`;
CREATE TABLE `insumo` (
  `id_insumo` int(11) NOT NULL,
  `nombre` varchar(30) NOT NULL,
  `precio_compra` float NOT NULL,
  `existencias` int(11) NOT NULL,
  `presentacion` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `insumo`
--

TRUNCATE TABLE `insumo`;
-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `lista_ingrediente`
--

DROP TABLE IF EXISTS `lista_ingrediente`;
CREATE TABLE `lista_ingrediente` (
  `id_elemento_lista` int(11) NOT NULL,
  `id_platillo` int(11) NOT NULL,
  `id_ingrediente` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `lista_ingrediente`
--

TRUNCATE TABLE `lista_ingrediente`;
-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mesa`
--

DROP TABLE IF EXISTS `mesa`;
CREATE TABLE `mesa` (
  `numero_mesa` int(11) NOT NULL,
  `estado` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `mesa`
--

TRUNCATE TABLE `mesa`;
--
-- Volcado de datos para la tabla `mesa`
--

INSERT INTO `mesa` (`numero_mesa`, `estado`) VALUES
(1, 'Libre'),
(2, 'Libre'),
(3, 'Libre'),
(4, 'Libre'),
(5, 'Libre'),
(6, 'Libre'),
(7, 'Libre'),
(8, 'Libre'),
(9, 'Libre'),
(10, 'Libre'),
(11, 'Libre'),
(12, 'Libre'),
(13, 'Libre'),
(14, 'Libre'),
(15, 'Libre'),
(16, 'Libre'),
(17, 'Libre'),
(18, 'Libre'),
(19, 'Libre'),
(20, 'Libre'),
(21, 'Libre'),
(22, 'Ocupada'),
(23, 'Libre'),
(24, 'Libre'),
(25, 'Libre');

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

--
-- Truncar tablas antes de insertar `pedido`
--

TRUNCATE TABLE `pedido`;
--
-- Volcado de datos para la tabla `pedido`
--

INSERT INTO `pedido` (`id_Pedido`, `comentario`, `Comanda_id_comanda`, `Platillo_id_platillo`, `estado`) VALUES
(1, 'Sin cebolla', 1, 8, 'En proceso');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `pedido_extra`
--

DROP TABLE IF EXISTS `pedido_extra`;
CREATE TABLE `pedido_extra` (
  `id_pedido_extra` int(11) NOT NULL,
  `id_extra` int(11) NOT NULL,
  `id_Pedido` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `pedido_extra`
--

TRUNCATE TABLE `pedido_extra`;
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
-- Truncar tablas antes de insertar `platillo`
--

TRUNCATE TABLE `platillo`;
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
(55, 31, 'Cerveza', 'Bebidas Pal\' Alma', 'disponibles', '../fotos_menu/huevos.jpg'),
(56, 39, 'Michelada', 'Bebidas Pal\' Alma', 'disponibles', '../fotos_menu/huevos.jpg'),
(57, 47, 'Chelada', 'Bebidas Pal\' Alma', 'disponibles', '../fotos_menu/huevos.jpg'),
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

--
-- Truncar tablas antes de insertar `ticket`
--

TRUNCATE TABLE `ticket`;
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
-- Truncar tablas antes de insertar `tipo`
--

TRUNCATE TABLE `tipo`;
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
-- Estructura de tabla para la tabla `transaccion`
--

DROP TABLE IF EXISTS `transaccion`;
CREATE TABLE `transaccion` (
  `id_transaccion` int(11) NOT NULL,
  `fecha_hora` datetime NOT NULL,
  `cantidad` int(11) NOT NULL,
  `tipo` varchar(30) NOT NULL,
  `comentario` varchar(100) NOT NULL,
  `clave` int(11) NOT NULL,
  `id_insumo` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Truncar tablas antes de insertar `transaccion`
--

TRUNCATE TABLE `transaccion`;
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
-- Truncar tablas antes de insertar `usuario`
--

TRUNCATE TABLE `usuario`;
--
-- Volcado de datos para la tabla `usuario`
--

INSERT INTO `usuario` (`clave`, `apellido_paterno`, `apellido_materno`, `nombre`, `Tipo_id_tipo`) VALUES
(100, 'Carmona', 'Avendaño', 'Lluvia', 2);

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
-- Indices de la tabla `extra`
--
ALTER TABLE `extra`
  ADD PRIMARY KEY (`id_extra`);

--
-- Indices de la tabla `ingrediente`
--
ALTER TABLE `ingrediente`
  ADD PRIMARY KEY (`id_ingrediente`),
  ADD UNIQUE KEY `id_insumo` (`id_insumo`);

--
-- Indices de la tabla `insumo`
--
ALTER TABLE `insumo`
  ADD PRIMARY KEY (`id_insumo`);

--
-- Indices de la tabla `lista_ingrediente`
--
ALTER TABLE `lista_ingrediente`
  ADD PRIMARY KEY (`id_elemento_lista`),
  ADD KEY `id_platillo` (`id_platillo`),
  ADD KEY `id_ingrediente` (`id_ingrediente`);

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
-- Indices de la tabla `pedido_extra`
--
ALTER TABLE `pedido_extra`
  ADD PRIMARY KEY (`id_pedido_extra`),
  ADD KEY `id_extra` (`id_extra`),
  ADD KEY `id_Pedido` (`id_Pedido`);

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
-- Indices de la tabla `transaccion`
--
ALTER TABLE `transaccion`
  ADD PRIMARY KEY (`id_transaccion`),
  ADD KEY `clave` (`clave`),
  ADD KEY `id_insumo` (`id_insumo`);

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
  MODIFY `id_comanda` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT de la tabla `extra`
--
ALTER TABLE `extra`
  MODIFY `id_extra` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `ingrediente`
--
ALTER TABLE `ingrediente`
  MODIFY `id_ingrediente` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `insumo`
--
ALTER TABLE `insumo`
  MODIFY `id_insumo` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `lista_ingrediente`
--
ALTER TABLE `lista_ingrediente`
  MODIFY `id_elemento_lista` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `mesa`
--
ALTER TABLE `mesa`
  MODIFY `numero_mesa` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT de la tabla `pedido`
--
ALTER TABLE `pedido`
  MODIFY `id_Pedido` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `pedido_extra`
--
ALTER TABLE `pedido_extra`
  MODIFY `id_pedido_extra` int(11) NOT NULL AUTO_INCREMENT;

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
  MODIFY `clave` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=101;

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
-- Filtros para la tabla `ingrediente`
--
ALTER TABLE `ingrediente`
  ADD CONSTRAINT `ingrediente_ibfk_1` FOREIGN KEY (`id_insumo`) REFERENCES `insumo` (`id_insumo`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `lista_ingrediente`
--
ALTER TABLE `lista_ingrediente`
  ADD CONSTRAINT `lista_ingrediente_ibfk_1` FOREIGN KEY (`id_platillo`) REFERENCES `platillo` (`id_platillo`),
  ADD CONSTRAINT `lista_ingrediente_ibfk_2` FOREIGN KEY (`id_ingrediente`) REFERENCES `ingrediente` (`id_ingrediente`);

--
-- Filtros para la tabla `pedido`
--
ALTER TABLE `pedido`
  ADD CONSTRAINT `fk_Pedido_Platillo1` FOREIGN KEY (`Platillo_id_platillo`) REFERENCES `platillo` (`id_platillo`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `pedido_ibfk_1` FOREIGN KEY (`Comanda_id_comanda`) REFERENCES `comanda` (`id_comanda`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `pedido_extra`
--
ALTER TABLE `pedido_extra`
  ADD CONSTRAINT `pedido_extra_ibfk_1` FOREIGN KEY (`id_extra`) REFERENCES `extra` (`id_extra`),
  ADD CONSTRAINT `pedido_extra_ibfk_2` FOREIGN KEY (`id_Pedido`) REFERENCES `pedido` (`id_Pedido`);

--
-- Filtros para la tabla `ticket`
--
ALTER TABLE `ticket`
  ADD CONSTRAINT `fk_Ticket_Comanda1` FOREIGN KEY (`Comanda_id_comanda`) REFERENCES `comanda` (`id_comanda`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `transaccion`
--
ALTER TABLE `transaccion`
  ADD CONSTRAINT `transaccion_ibfk_1` FOREIGN KEY (`clave`) REFERENCES `usuario` (`clave`),
  ADD CONSTRAINT `transaccion_ibfk_2` FOREIGN KEY (`id_insumo`) REFERENCES `insumo` (`id_insumo`);

--
-- Filtros para la tabla `usuario`
--
ALTER TABLE `usuario`
  ADD CONSTRAINT `fk_Usuario_Tipo` FOREIGN KEY (`Tipo_id_tipo`) REFERENCES `tipo` (`id_tipo`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
