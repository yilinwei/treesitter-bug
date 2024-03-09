#include <tree_sitter/api.h>
#include <stdio.h>
#include <string.h>

const TSLanguage *tree_sitter_scala(void);

int main(int argc, char *argv[]) {

  int exit_code = 0;

  const char *file_name = "test.scala3";
  const char *field = "body";
  
  FILE* file = fopen(file_name, "rb");

  if (file == NULL) {
    exit_code = 1;
    fprintf(stderr, "could not open test file %s", file_name);
    goto exit;
  }
  
  fseek(file, 0L, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char *source_code = malloc(size);
  if (fread(source_code, size, 1, file) == 0) {
    exit_code = 1;
    goto cleanup;
  }

  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_scala());
  TSTree *tree = ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));
  TSNode root_node = ts_tree_root_node(tree);
  
  char *string = ts_node_string(root_node);
  printf("Full syntax tree: %s\n", string);

  TSNode node = ts_node_named_child(root_node, 0);
  node = ts_node_named_child(root_node, 0);
  node = ts_node_child_by_field_name(node, field, strlen(field));
  string = ts_node_string(node);
  printf("node via `node_child_by_field_name`: %s\n", string);

  TSNode parent = ts_node_parent(node);
  uint32_t count = ts_node_child_count(parent);
  for (int i = 0; i < count; i++) {
    const char* field_name = ts_node_field_name_for_child(parent, i);
    if (field_name != NULL && strcmp(field_name, field) == 0) {
      TSNode child = ts_node_child(parent, i);
      string = ts_node_string(child);
      printf("node via `field_name_for_child`: %s\n", string);
    } 
  }
  ts_parser_delete(parser);

 cleanup:
  fclose(file);

 exit:
  exit(exit_code);
}
