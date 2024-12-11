// CREATE (n: Person {name: 'Daniel Radcliffe', born: 1989}),
// (n:Person {name: "Johnny Depp", born: 1963}),
// (n:Person {name: "Quentin Tarantino", born: 1963});

// MATCH (n:Person)
MATCH (n:Person)
WHERE n.name IN ["Johnny Depp", "Quentin Tarantino"]
RETURN n;