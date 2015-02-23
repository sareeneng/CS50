--
-- Database: `pset7`
--

CREATE DATABASE IF NOT EXISTS  `pset7`;


--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `pset7`.`users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=7;

--
-- Dumping data for table `pset7`.`users`
--

INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(1, 'belindazeng', '$1$50$oxJEDBo9KDStnrhtnSzir0');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(2, 'caesar', '$1$50$GHABNWBNE/o4VL7QjmQ6x0');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(3, 'jharvard', '$1$50$RX3wnAMNrGIbgzbRYrxM1/');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(4, 'malan', '$1$50$lJS9HiGK6sphej8c4bnbX.');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(5, 'rob', '$1$HA$l5llES7AEaz8ndmSo5Ig41');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(6, 'skroob', '$1$50$euBi4ugiJmbpIbvTTfmfI.');
INSERT INTO `pset7`.`users` (`id`, `username`, `hash`) VALUES(7, 'zamyla', '$1$50$uwfqB45ANW.9.6qaQ.DcF.');
