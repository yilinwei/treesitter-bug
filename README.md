This uses the current HEAD grammar for Scala [here](https://github.com/tree-sitter/tree-sitter-scala).

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

