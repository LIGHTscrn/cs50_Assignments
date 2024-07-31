-- Keep a log of any SQL queries you execute as you solve the mystery.
FIRST check crime scene report
    SELECT description FROM crime_scene_report WHERE day = '28' AND year = '2023' AND street = 'Humphrey Street';
        SO two crimes took place on that day, first being the theft of cs50duck at 10:15am interviews were conducted with three witnesses and all mentioned bakery
        second crime being littering at 16:36 with no witnesses
SECONG check INTERVIEWS
    SELECT * FROM interviews WHERE day = '28' AND year = 2023 AND month = '7';
    witness 1 :ruth provided some crucial information : After 10 minutes of theft the thief left in a car parked inside bakery parking lot
    witness 2:Eugene saw the thief withdrawing money this morning by an ATM on Leggett Street at emas bakery;
    witness 3:while leaving the thief phone called someone and talked for less than a minute. the witness overheard the thief talking about earliest flight out of fiftyville next day and to buy the flight tickets;
     working on witness 1s information:
     after 10 minutes so car left from the bakery between 10:15 and 10:25
     SELECT * FROM bakery_security_logs WHERE year = '2023' AND day = '28' AND month = '7';
     8 exists match the description from ruths descloser
     1: 10:23 : 0NTHK55
     2: 10:23 : 322W7JE
     3: 10:21 : L93JTIZ
     4: 10:20 : G412GB7
     5: 10:19 : 4328GD8
     6: 10:18 : 6P58WS2
     7: 10:18 : 94KL13X
     8: 10:16 : 5P2BI95

     Now working on witness 2s information
     SELECT * FROM atm_transactions WHERE (year,month,day,atm_location) = ('2023','7','28','Leggett Street');
     SELECT * FROM flights WHERE (year,month,day) = ('2023','7','29');
     +----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

sqlite> SELECT * FROM passengers WHERE flight_id = 36;
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |
+-----------+-----------------+------+

     NOW working on witness 3s information
     sqlite> SELECT * FROM phone_calls WHERE (year,month,day) = ('2023','7','28') AND duration < '60';
 SELECT * FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN bakery_security_logs  WHERE passengers.flight_id = 36 AND people.license_plate IN (SELECT bakery_security_logs.license_plate WHERE (year,month,day) = ('2023','7','28') AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 25 AND bakery_security_logs.minute > 15);

  SELECT people.name,people.phone_number FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN bakery_security_logs  WHERE passengers.flight_id = 36 AND people.license_plate IN (SELECT bakery_security_logs.license_plate WHERE (year,month,day) = ('2023','7','28') AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 25 AND bakery_security_logs.minute > 15) AND people.phone_number IN (SELECT caller FROM phone_calls WHERE (year,month,day) = ('2023','7','28') AND duration < '60');




