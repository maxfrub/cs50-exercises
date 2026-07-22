-- Keep a log of any SQL queries you execute as you solve the mystery.

--Consult crime_scenes_reports table
SELECT *
FROM crime_scene_reports
WHERE day = 28 AND month = 7;
--10:15 am a the Humphrey Street bakery. Three witnesses mention the bakery.

--See interviews
SELECT *
FROM interviews
WHERE month = 7 AND day = 28;
--IMPORTANT INFO:
--Within 10 min, the thief got into a car.
--Earlier, he was at the ATM on Leggett Street withdrawing some money.
--When he was leaving the bakery, he called someone for less than a minute. They were planning to take the earliees flight of Fiftyville on 29.
--He asked to buy the ticket.

--See a phone call within the time range that lasts for less than 1 min.
SELECT *
FROM phone_calls
WHERE month = 7 and day = 28;
--There are some calls that lasts for less than 1 min, so I need to see who is the thief first.

--See bakery cameras
SELECT *
FROM bakery_security_logs
WHERE month = 7 AND day = 28;
--Too many people entering the bakery, I need to see the ATM.

--See the ATM and search for "leggett street"
SELECT *
FROM atm_transactions
WHERE month = 7
AND day = 28
AND atm_location = 'Leggett Street';

--Search for people that used the ATM the same day on "legget street" and was on the bakery and did a call
SELECT DISTINCT people.name, phone_calls.receiver, flights.destination_airport_id
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls
ON people.phone_number = phone_calls.caller
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON flights.id = passengers.flight_id
JOIN airports
ON flights.origin_airport_id = airports.id
WHERE bakery_security_logs.day = 28 AND bakery_security_logs.month = 7
AND bakery_security_logs.activity = 'exit'
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute < 26
AND phone_calls.day = 28 AND phone_calls.month = 7
AND phone_calls.duration < 60
AND atm_transactions.day = 28 AND atm_transactions.month = 7
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND flights.id = (
    SELECT id
    FROM flights
    WHERE year = 2025
    AND month = 7
    AND day = 29
    AND origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute
    LIMIT 1
);
--The thief is Bruce

--Now search the complice:
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161'
--The complice is Robin

--Now where the flight of Bruce went to
SELECT city
FROM airports
WHERE id = 4;
--The city is New York City
