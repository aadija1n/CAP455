# Project Proposal

## Title
Bike Service Interval Reminder Console

## Problem
Bike owners may forget routine maintenance such as engine-oil changes, chain lubrication and brake checks. This console application stores bike and last-service details and shows whether a service is due by distance travelled or days passed.

## Objectives
- Store basic information for multiple bikes.
- Use registration number as a unique key.
- Reject empty registration numbers, duplicate keys and invalid negative values.
- Keep records after the program closes using a binary data file.
- Search, update and delete records.
- Display service reminders and provide a simple backup/export option.

## Main entity and key
The main entity is `Bike`. Its unique key is `regNo` (registration number).

## Main class
`Bike` stores registration number, owner name, model, current kilometres, last-service kilometres, kilometre interval, days since service and day interval. `CommuterBike` and `SportsBike` are derived classes used to demonstrate inheritance and polymorphism.

## Inputs and outputs
Inputs are entered through a numbered console menu. Outputs include bike details, service due/not-due status, search results and file-operation messages.

## Scope
This is an educational console project. It does not connect to a real workshop, vehicle database or calendar service.
