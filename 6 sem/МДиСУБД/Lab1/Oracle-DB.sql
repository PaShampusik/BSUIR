DECLARE
    l_total_reward NUMBER;
BEGIN
    l_total_reward := calculate_total_reward(100, -100);
    DBMS_OUTPUT.PUT_LINE('Общее вознаграждение: ' || l_total_reward);
END;
/