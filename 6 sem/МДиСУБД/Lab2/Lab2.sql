--groups
CREATE TABLE groups (
    id NUMBER NOT NULL,
    group_name VARCHAR2(20) NOT NULL,
    C_VAL NUMBER NOT NULL,
    CONSTRAINT group_id_pk PRIMARY KEY (id)
) -- students
CREATE TABLE students (
    student_id NUMBER NOT NULL,
    student_name VARCHAR2(20) NOT NULL,
    gr_id NUMBER NOT NULL,
    CONSTRAINT student_id_pk PRIMARY KEY (student_id),
    CONSTRAINT group_id_fk FOREIGN KEY (gr_id) REFERENCES groups (id)
) --groups id_name_unique trigger
CREATE OR REPLACE TRIGGER check_group_id_name_uniqueness BEFORE
INSERT
    OR
UPDATE ON groups FOR EACH ROW
DECLARE duplicate_id_count NUMBER;
duplicate_name_count NUMBER;
BEGIN IF INSERTING
OR UPDATING('ID') THEN
SELECT COUNT(*) INTO duplicate_id_count
FROM groups
WHERE id = :new.id;
IF duplicate_id_count > 0 THEN RAISE_APPLICATION_ERROR(-20001, 'group_id must be unique');
END IF;
END IF;
IF INSERTING
OR UPDATING('GROUP_NAME') THEN
SELECT COUNT(*) INTO duplicate_name_count
FROM groups
WHERE LOWER(group_name) = LOWER(:new.group_name);
IF duplicate_name_count > 0 THEN RAISE_APPLICATION_ERROR(-20001, 'group_name must be unique');
END IF;
END IF;
END;
--seq for autoincr trigger
CREATE SEQUENCE GROUP_ID_SEQ START WITH 1;
--groups id_autoincr trigger
CREATE OR REPLACE TRIGGER group_id_autoinc BEFORE
INSERT ON groups FOR EACH ROW BEGIN :NEW.id := GROUP_ID_SEQ.NEXTVAL;
END;
--student id unique trigger
CREATE OR REPLACE TRIGGER check_student_id_uniqueness BEFORE
INSERT ON students FOR EACH ROW
DECLARE duplicate_count NUMBER;
BEGIN
SELECT COUNT(*) INTO duplicate_count
FROM students
WHERE student_id = :new.student_id;
IF duplicate_count > 0 THEN RAISE_APPLICATION_ERROR(
    -20001,
    'Student ID must be unique ' || :new.student_id
);
END IF;
END;
--seq for autoincr trigger
CREATE SEQUENCE STUDENT_ID_SEQ START WITH 1;
--student id_autoincr trigger
CREATE OR REPLACE TRIGGER student_id_autoinc BEFORE
INSERT ON students FOR EACH ROW BEGIN IF :NEW.STUDENT_ID IS NULL THEN :NEW.STUDENT_ID := STUDENT_ID_SEQ.NEXTVAL;
END IF;
END;
--cascade delete of students from group before deleting group trigger
CREATE OR REPLACE TRIGGER cascade_delete_students BEFORE DELETE ON groups FOR EACH ROW BEGIN
DELETE FROM students
WHERE gr_id = :old.id;
END;
--logging all students manipulations trigger
CREATE OR REPLACE TRIGGER students_log_trigger
AFTER
INSERT
    OR
UPDATE
    OR DELETE ON students FOR EACH ROW BEGIN IF INSERTING THEN
INSERT INTO students_log (
        log_id,
        action,
        new_student_id,
        student_name,
        gr_id,
        action_date
    )
VALUES (
        students_log_seq.nextval,
        'INSERT',
        :new.student_id,
        :new.student_name,
        :new.gr_id,
        SYSTIMESTAMP
    );
ELSIF UPDATING THEN
INSERT INTO students_log (
        log_id,
        action,
        old_student_id,
        new_student_id,
        student_name,
        gr_id,
        action_date
    )
VALUES (
        students_log_seq.nextval,
        'UPDATE',
        :old.student_id,
        :new.student_id,
        :new.student_name,
        :new.gr_id,
        SYSTIMESTAMP
    );
ELSIF DELETING THEN
INSERT INTO students_log (
        log_id,
        action,
        old_student_id,
        student_name,
        gr_id,
        action_date
    )
VALUES (
        students_log_seq.nextval,
        'DELETE',
        :old.student_id,
        :old.student_name,
        :old.gr_id,
        SYSTIMESTAMP
    );
END IF;
END --recovery procedure
CREATE OR REPLACE PROCEDURE restore_students_state(p_timestamp TIMESTAMP) IS cur_time TIMESTAMP;
BEGIN cur_time := SYSTIMESTAMP;
DELETE FROM students;
FOR lg IN (
    SELECT *
    FROM students_log
    WHERE action_date <= p_timestamp
    ORDER BY action_date
) LOOP IF lg.action = 'INSERT' THEN
INSERT INTO students (student_id, student_name, gr_id)
VALUES (lg.new_student_id, lg.student_name, lg.gr_id);
ELSIF lg.action = 'UPDATE' THEN
UPDATE students
SET student_name = lg.student_name,
    gr_id = lg.gr_id,
    student_id = lg.new_student_id
WHERE student_id = lg.old_student_id;
ELSIF lg.action = 'DELETE' THEN
DELETE FROM students
WHERE student_id = lg.old_student_id;
END IF;
END LOOP;
DELETE FROM students_log
WHERE action_date >= cur_time;
END;
--update c_val trigger
CREATE OR REPLACE TRIGGER update_c_val_trigger
AFTER
INSERT
    OR
UPDATE
    OR DELETE ON students FOR EACH ROW
DECLARE new_group_id NUMBER;
old_group_id NUMBER;
BEGIN IF INSERTING THEN
UPDATE groups
SET c_val = c_val + 1
WHERE id = :NEW.gr_id;
ELSIF UPDATING THEN new_group_id := :NEW.gr_id;
old_group_id := :OLD.gr_id;
IF new_group_id <> old_group_id THEN
UPDATE groups
SET c_val = c_val + 1
WHERE id = new_group_id;
UPDATE groups
SET c_val = c_val - 1
WHERE id = old_group_id;
END IF;
ELSIF DELETING THEN
UPDATE groups
SET c_val = c_val - 1
WHERE id = :OLD.gr_id;
END IF;
END;