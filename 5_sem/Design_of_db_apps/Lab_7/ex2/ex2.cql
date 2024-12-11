MATCH (f:Movie {title: 'Forrest Gump'})
SET f.genre = 'Drama', f.duration = 142;

MATCH (m:Movie {title: 'The Matrix'})
SET m.released = 2000;

MATCH (Keanu:Person {name: 'Keanu Reeves'})-[r:ACTED_IN]->(m:Movie {title: 'The Matrix'})
DELETE r;
