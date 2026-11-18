# UML Class Diagram (text form)

```text
                 +-----------------------------+
                 |             Bike            |
                 +-----------------------------+
                 | - regNo : string            |
                 | - ownerName : string        |
                 | - model : string            |
                 | - currentKm : int           |
                 | - lastServiceKm : int       |
                 | - serviceIntervalKm : int   |
                 | - daysSinceService : int    |
                 | - serviceIntervalDays : int |
                 | - totalBikes : static int   |
                 +-----------------------------+
                 | + constructors              |
                 | + virtual destructor        |
                 | + display() : void          |
                 | + isServiceDue() : bool     |
                 | + operators < > == +=       |
                 | + operator int()            |
                 +-----------------------------+
                    ^                    ^
                    |                    |
       +----------------------+  +----------------------+
       |     CommuterBike     |  |      SportsBike      |
       +----------------------+  +----------------------+
       | + getBikeType()      |  | + getBikeType()      |
       | + getSuggested...()  |  | + getSuggested...()  |
       +----------------------+  +----------------------+

       BikeManager contains an array of Bike pointers and manages
       create/read/search/update/delete, file storage and reports.
```
