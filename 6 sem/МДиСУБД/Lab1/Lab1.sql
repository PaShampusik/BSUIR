-- Creating table
CREATE TABLE MyTable (id NUMBER, val NUMBER);
--Заполнение 10000 случайными щапиисями
BEGIN FOR i IN 1..10000 LOOP
INSERT INTO MyTable (id, val)
VALUES (i, ROUND(DBMS_RANDOM.VALUE(1, 10000)));
END LOOP;
COMMIT;
END;
--Check even odd fucntion
CREATE OR REPLACE FUNCTION check_even_odd RETURN VARCHAR2 AS v_even_count NUMBER;
v_odd_count NUMBER;
BEGIN
SELECT COUNT(
    CASE
      WHEN MOD(val, 2) = 0 THEN 1
    END
  ) INTO v_even_count
FROM MyTable;
SELECT COUNT(
    CASE
      WHEN MOD(val, 2) = 1 THEN 1
    END
  ) INTO v_odd_count
FROM MyTable;
IF v_even_count > v_odd_count THEN RETURN 'TRUE';
ELSIF v_even_count < v_odd_count THEN RETURN 'FALSE';
ELSE RETURN 'EQUAL';
END IF;
END;
--example of usage
SELECT CHECK_EVEN_ODD()
FROM dual;
-- func for generating insert command
CREATE OR REPLACE FUNCTION generate_insert_command(p_id NUMBER) RETURN VARCHAR2 AS v_insert_command VARCHAR2(4000);
BEGIN v_insert_command := 'INSERT INTO MyTable (id, val) VALUES (' || p_id || ', <значение_val>);';
DBMS_OUTPUT.PUT_LINE(v_insert_command);
RETURN v_insert_command;
END;
/ --example of usage
SELECT GENERATE_INSERT_COMMAND(10)
FROM dual;
--DML
--Insert
CREATE OR REPLACE PROCEDURE insert_data(p_id NUMBER, p_val NUMBER) AS BEGIN
INSERT INTO MyTable (id, val)
VALUES (p_id, p_val);
COMMIT;
END;
/ --Update
CREATE OR REPLACE PROCEDURE update_data(p_id NUMBER, p_new_val NUMBER) AS BEGIN
UPDATE MyTable
SET val = p_new_val
WHERE id = p_id;
COMMIT;
END;
/ --Delete
CREATE OR REPLACE PROCEDURE delete_data(p_id NUMBER) AS BEGIN
DELETE FROM MyTable
WHERE id = p_id;
COMMIT;
END;
/ --example of usage
BEGIN insert_data(< ваше_значение_id >, < ваше_значение_val >);
END;
--Reward
create or replace NONEDITIONABLE FUNCTION calculate_total_reward(
    p_monthly_salary IN NUMBER,
    p_annual_bonus_percentage IN INTEGER
  ) RETURN NUMBER IS l_annual_bonus_percentage NUMBER;
l_total_reward NUMBER;
BEGIN IF p_annual_bonus_percentage < 0
OR p_monthly_salary < 0 THEN RAISE INVALID_NUMBER;
END IF;
IF NOT REGEXP_LIKE(p_annual_bonus_percentage, '^[[:digit:]]+$') THEN RAISE VALUE_ERROR;
END IF;
-- Преобразуем процент в дробное число
l_annual_bonus_percentage := p_annual_bonus_percentage / 100.0;
-- Вычисляем общее вознаграждение
l_total_reward := (1 + l_annual_bonus_percentage) * 12 * p_monthly_salary;
RETURN l_total_reward;
EXCEPTION
WHEN INVALID_NUMBER THEN DBMS_OUTPUT.PUT_LINE('Неверный формат ввода' || SQLERRM);
RETURN NULL;
WHEN VALUE_ERROR THEN DBMS_OUTPUT.PUT_LINE('Нельзя строки' || SQLERRM);
RETURN NULL;
WHEN OTHERS THEN -- Обработка исключений
DBMS_OUTPUT.PUT_LINE('Произошла ошибка: ' || SQLERRM);
RETURN NULL;
-- Или другое значение, указывающее на ошибку
END;
--example of usage
DECLARE l_total_reward NUMBER;
BEGIN l_total_reward := calculate_total_reward(100, -100);
DBMS_OUTPUT.PUT_LINE('Общее вознаграждение: ' || l_total_reward);
END;
/