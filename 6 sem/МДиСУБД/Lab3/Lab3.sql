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
ddl_script := '';
DECLARE data_type VARCHAR2(100);
data_length NUMBER;
data_precision NUMBER;
BEGIN FOR i IN 1..dev_columns_set.count LOOP IF dev_columns_set(i) NOT MEMBER OF prod_columns_set THEN
SELECT data_type,
    data_length,
    data_precision INTO data_type,
    data_length,
    data_precision
FROM all_tab_columns
WHERE owner = dev_schema_name
    AND table_name = p_table_name
    AND column_name = dev_columns_set(i);
ddl_script := ddl_script || 'ALTER TABLE ' || p_table_name || ' ADD COLUMN ' || dev_columns_set(i) || ' ' || data_type;
IF data_type IN ('VARCHAR2', 'NVARCHAR2', 'RAW')
AND data_length IS NOT NULL THEN ddl_script := ddl_script || '(' || data_length || ')';
ELSIF data_type IN ('NUMBER')
AND data_precision IS NOT NULL THEN ddl_script := ddl_script || '(' || data_precision || ')';
END IF;
ddl_script := ddl_script || chr(10);
END IF;
END LOOP;
END;
FOR i IN 1..dev_constraints_set.count LOOP IF dev_constraints_set(i) NOT MEMBER OF prod_constraints_set THEN
DECLARE ddl_script CLOB;
constraint_type VARCHAR2(20);
BEGIN
SELECT constraint_type INTO constraint_type
FROM all_constraints
WHERE owner = dev_schema_name
    AND table_name = p_table_name
    AND constraint_name = dev_constraints_set(i);
ddl_script := ddl_script || dbms_metadata.get_ddl(
    CASE
        WHEN constraint_type = 'R' THEN 'REF_CONSTRAINT'
        ELSE 'CONSTRAINT'
    END,
    dev_constraints_set(i),
    dev_schema_name
);
ddl_script := ddl_script || chr(10);
END;
END IF;
END LOOP;
FOR i IN 1..prod_columns_set.count LOOP IF prod_columns_set(i) NOT MEMBER OF dev_columns_set THEN ddl_script := ddl_script || 'ALTER TABLE ' || prod_schema_name || '.' || p_table_name || ' DROP COLUMN ' || prod_columns_set(i) || ';' || chr(10);
END IF;
END LOOP;
FOR i IN 1..prod_constraints_set.count LOOP IF prod_columns_set(i) NOT MEMBER OF dev_constraints_set THEN ddl_script := ddl_script || 'ALTER TABLE ' || prod_schema_name || '.' || p_table_name || ' DROP CONSTRAINT ' || prod_constraints_set(i) || ';' || chr(10);
END IF;
END LOOP;
dbms_output.put_line(
    'DDL-script for updating table ' || p_table_name || ' {' || chr(10)
);
ddl_script := replace(ddl_script, dev_schema_name, prod_schema_name);
dbms_output.put_line(ddl_script);
RETURN v_identical;
END are_tables_identical;