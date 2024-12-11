// Movies where Tom Hanks acted
MATCH(n: Person)-[:ACTED_IN]->(m: Movie)
WHERE n.name = 'Tom Hanks'
RETURN m.title;

// Movies where Tom Hanks acted and directed
MATCH(n: Person)-[:ACTED_IN]->(m: Movie)<-[:DIRECTED]-(n)
WHERE n.name = 'Tom Hanks'
RETURN m.title, n.name;

// Actors who did not act in any movie
MATCH (n: Person)
WHERE NOT (n)-[:ACTED_IN]->()
RETURN n.name;

// Actors who acted in more than one movie
MATCH (n:Person)-[:ACTED_IN]->(m:Movie)
WITH n, count(m) AS movieCount
WHERE movieCount > 2
RETURN n.name;

// Movie with the most actors
MATCH(n: Person)-[:ACTED_IN]->(m: Movie)
WITH m, count(n) AS ActorCount
ORDER BY ActorCount DESC
RETURN m.title AS MovieTitle, ActorCount
LIMIT 1;