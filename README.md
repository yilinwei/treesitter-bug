This uses the current HEAD commit of the grammar for Scala [here](https://github.com/tree-sitter/tree-sitter-scala/commit/e02f003d78dc269fef287b9b7b9963dc1f26bd7e).

```sh 
make build
./main
```

Output of code when running the program: 

```
Full syntax tree: (compilation_unit (function_definition name: (identifier) body: (indented_cases (case_clause pattern: (wildcard) body: (integer_literal)))))
node via `node_child_by_field_name`: (indented_cases (case_clause pattern: (wildcard) body: (integer_literal)))
node via `field_name_for_child`: ("=")
```

