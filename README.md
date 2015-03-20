# Distance Extension for SQLite

Dave Addey's SQLite extension for calculating distance using two pairs of
latitude/longitude coordinates for use with the sqlite cli.

## Building

#### Linux

```
$ make
```

## Usage

```
$ sqlite3 -cmd '.load ./distance' example.sqlite
sqlite> SELECT name FROM location ORDER BY DISTANCE(latitude, longitude, 33.8120742,-117.9188774) LIMIT 10;
```

## Credits
Dave Addey <a href="http://daveaddey.com/?p=71">wrote the SQLite extension</a>.
I just wrapped it up for use on the command line.
