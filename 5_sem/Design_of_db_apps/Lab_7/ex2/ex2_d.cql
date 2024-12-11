MATCH (Johnny:Person {name: 'Johnny Depp'}), (Pirates:Movie {title: 'Pirates of the Caribbean'})
CREATE (Johnny)-[:ACTED_IN {roles: ['Capitan Jack Sparrow']}]->(Pirates);

MATCH (Daniel: Person {name: 'Daniel Radcliffe'}), (HarryPotter: Movie {title: 'Harry Potter and the Philosopher\'s Stone'})
CREATE (Daniel)-[:ACTED_IN {roles: ['Harry Potter']}]->(HarryPotter);