# Data Dictionary

| Field | Type | Meaning / validation |
|---|---|---|
| `regNo` | `std::string` / `char[25]` in file | Unique bike registration; cannot be empty or duplicated |
| `ownerName` | `std::string` / `char[50]` | Bike owner's name; cannot be empty |
| `model` | `std::string` / `char[50]` | Bike model; cannot be empty |
| `bikeType` | `std::string` / `char[15]` | Regular, Commuter or Sports |
| `currentKm` | `int` | Current odometer reading; non-negative |
| `lastServiceKm` | `int` | Odometer reading at last service; non-negative and not above current KM |
| `serviceIntervalKm` | `int` | Kilometres between services; positive |
| `daysSinceService` | `int` | Days since last service; non-negative |
| `serviceIntervalDays` | `int` | Maximum days between services; positive |

The binary `BikeRecord` structure uses fixed-size character arrays and integer fields. This makes the record size constant, which allows the program to move to a record using `seekg` and `seekp`.
