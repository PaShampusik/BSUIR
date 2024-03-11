CREATE OR REPLACE PROCEDURE compare_schemas (
        dev_schema_name IN VARCHAR2,
        prod_schema_name IN VARCHAR2
    ) AS TYPE string_list_t IS TABLE OF VARCHAR2(100);
dev_tables string_list_t := string_list_t();
prod_tables string_list_t := string_list_t();
visited_tables string_list_t := string_list_t();
sorted_tables string_list_t := string_list_t();
dev_procs string_list_t := string_list_t();
prod_procs string_list_t := string_list_t();
dev_only_procs string_list_t := string_list_t();
prod_only_procs string_list_t := string_list_t();
different_procs string_list_t := string_list_t();
dev_funcs string_list_t := string_list_t();
prod_funcs string_list_t := string_list_t();
dev_only_funcs string_list_t := string_list_t();
prod_only_funcs string_list_t := string_list_t();
different_funcs string_list_t := string_list_t();
dev_indexes string_list_t := string_list_t();
prod_indexes string_list_t := string_list_t();
dev_only_indexes string_list_t := string_list_t();
prod_only_indexes string_list_t := string_list_t();
ddl_script CLOB := '';
counter NUMBER;
FUNCTION are_tables_identical(p_table_name IN VARCHAR2) RETURN BOOLEAN IS v_identical BOOLEAN := true;
dev_constraints_set string_list_t;
prod_constraints_set string_list_t;
dev_columns_set string_list_t;
prod_columns_set string_list_t;
BEGIN
SELECT constraint_name BULK COLLECT INTO dev_constraints_set
FROM all_constraints
WHERE owner = dev_schema_name
    AND table_name = p_table_name
    AND constraint_name NOT LIKE 'SYS%'
ORDER BY constraint_name;
SELECT constraint_name BULK COLLECT INTO prod_constraints_set
FROM all_constraints
WHERE owner = prod_schema_name
    AND table_name = p_table_name
    AND constraint_name NOT LIKE 'SYS%'
ORDER BY constraint_name;
SELECT column_name BULK COLLECT INTO dev_columns_set
FROM all_tab_columns
WHERE owner = dev_schema_name
    AND table_name = p_table_name
    AND column_name NOT LIKE 'SYS%'
ORDER BY column_name;
SELECT column_name BULK COLLECT INTO prod_columns_set
FROM all_tab_columns
WHERE owner = prod_schema_name
    AND table_name = p_table_name
    AND column_name NOT LIKE 'SYS%'
ORDER BY column_name;
v_identical := true;
IF dev_constraints_set MULTISET
EXCEPT prod_constraints_set IS NOT EMPTY
    OR prod_constraints_set MULTISET
EXCEPT dev_constraints_set IS NOT EMPTY THEN v_identical := false;
END IF;
IF dev_columns_set MULTISET
EXCEPT prod_columns_set IS NOT EMPTY
    OR prod_columns_set MULTISET
EXCEPT dev_columns_set IS NOT EMPTY THEN v_identical := false;
END IF;
IF v_identical THEN RETURN v_identical;
END IF;