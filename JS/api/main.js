const tests = require('./tests');


for (const test in tests) {

    let success = false;
    try { success = tests[test](); }

    catch (exception) {
        console.log(exception);
        console.error("test not pass: " + test);
    }

    if (!success) {
        console.error("test not pass: " + test);
    }
}
