# Manual Test Cases

Run the program from the repository root after compiling it. Remove `data/bikes.dat` before a fresh test run if a clean data set is needed.

| ID | Test input/action | Expected result | Result |
|---|---|---|---|
| T01 | Add a bike with a new registration number and valid values | Record is added | To be verified during live demo |
| T02 | Add another bike with the same registration number | Duplicate is rejected | To be verified during live demo |
| T03 | Enter an empty registration number | Empty value is rejected | To be verified during live demo |
| T04 | Enter negative current KM | Input is rejected and re-prompted | To be verified during live demo |
| T05 | Enter last-service KM greater than current KM | Input is rejected | To be verified during live demo |
| T06 | Add records until 100, then add one more | Full-list message appears | To be verified during live demo |
| T07 | Exit and start program again | Previously saved records appear | To be verified during live demo |
| T08 | Search for an existing registration number | Matching bike is displayed | To be verified during live demo |
| T09 | Search for a missing registration number | Custom exception message appears | To be verified during live demo |
| T10 | Update current KM to a valid value | Record is updated and saved | To be verified during live demo |
| T11 | Delete a record and answer `n` | Deletion is cancelled | To be verified during live demo |
| T12 | Delete a record and answer `y`, then undo | Record is removed then restored | To be verified during live demo |
| T13 | Set distance or days at the service interval | Bike appears in service reminders | To be verified during live demo |
| T14 | Create backup and CSV export | Files appear under `data/` | To be verified during live demo |
| T15 | Sort bikes by current KM | Bikes display in ascending order | To be verified during live demo |
