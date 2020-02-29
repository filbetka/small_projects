const validator = require('./validator');


module.exports =
    {
        /**
         * Tests for `/user` endpoints
         */

        _user__post__positive: function () {
            return validator.validateUserPostRequest({
                user: 'example@example.com', // email is user name
                password: 'examplePassword1', // 8 characters+, one alphanumeric
                teamName: 'exampleTeamName', // name of team to display.
                eventId: 'XZ3bw1fn44hr', // key assigned to event
            });
        },

        _user__post__bad_user: function () {
            const state = validator.validateUserPostRequest({
                user: '123example.com', // email is user name
                password: 'examplePassword1', // 8 characters+, one alphanumeric
                teamName: 'exampleTeamName', // name of team to display.
                eventId: 'XZ3bw1fn44hr', // key assigned to event
            });

            if (state)
                return false;

            // check message
            // ...
            return true;
        },

        _user__post__password_without_number: function () {
            const state = validator.validateUserPostRequest({
                user: '123example.com', // email is user name
                password: 'examplePassword', // 8 characters+, one alphanumeric
                teamName: 'exampleTeamName', // name of team to display.
                eventId: 'XZ3bw1fn44hr', // key assigned to event
            });

            if (state)
                return false;

            // check message
            // ...
            return true;
        },

        _user__post__password_too_short: function () {
            const state = validator.validateUserPostRequest({
                user: '123example.com', // email is user name
                password: 'exa1', // 8 characters+, one alphanumeric
                teamName: 'exampleTeamName', // name of team to display.
                eventId: 'XZ3bw1fn44hr', // key assigned to event
            });

            if (state)
                return false;

            // check message
            // ...
            return true;
        },

        _user__post__teamName_empty: function () {
            const state = validator.validateUserPostRequest({
                user: '123example.com', // email is user name
                password: 'examplePassword1', // 8 characters+, one alphanumeric
                teamName: '',
                eventId: 'XZ3bw1fn44hr', // key assigned to event
            });

            if (state)
                return false;

            // check message
            // ...
            return true;
        },

        _user__post__eventId_empty: function () {
            const state = validator.validateUserPostRequest({
                user: '123example.com', // email is user name
                password: 'examplePassword1', // 8 characters+, one alphanumeric
                teamName: 'exampleTeamName', // name of team to display.
                eventId: '', // key assigned to event
            });

            if (state)
                return false;

            // check message
            // ...
            return true;
        },

        _user_remind__post__positive: function () {
            return validator.validateUserRemindPostRequest({
                user: 'example@example.com', // email is user name
            });
        },

        _user_remind__put__positive: function () {
            return validator.validateUserRemindPutRequest({
                password: 'examplePassword1', // 8 characters+, one alphanumeric
            });
        },

        /**
         * Tests for `/event` endpoints
         */

        _event__get: function () {
        },

        _event__post: function () {
        },

        _event__put: function () {
        },

        _event_collect__put: function () {
        },
    };
