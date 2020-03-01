const validator = require('./validator');


module.exports =
    {
        /**
         * Tests for `/user` endpoint
         */

        _user__post__positive: function () {
            validator.validateUserPostRequest({
                user: 'example@example.com', // email is user name
                password: 'examplePassword1', // 8 characters+, one alphanumeric
                teamName: 'exampleTeamName', // name of team to display.
                eventId: 'XZ3bw1fn44hr', // key assigned to event
            });

            return true;
        },

        _user__post__bad_user: function () {
            try {
                validator.validateUserPostRequest({
                    user: '123example.com', // email is user name
                    password: 'examplePassword1', // 8 characters+, one alphanumeric
                    teamName: 'exampleTeamName', // name of team to display.
                    eventId: 'XZ3bw1fn44hr', // key assigned to event
                });
            }

            catch (exception) {
                if (exception === 'user field is not email')
                    return true;
            }

            return false;
        },

        _user__post__password_without_number: function () {
            try {
                validator.validateUserPostRequest({
                    user: 'example@example.com', // email is user name
                    password: 'examplePassword', // 8 characters+, one alphanumeric
                    teamName: 'exampleTeamName', // name of team to display.
                    eventId: 'XZ3bw1fn44hr', // key assigned to event
                });
            }

            catch (exception) {
                if (exception === 'password has not number')
                    return true;
            }

            return false;
        },

        _user__post__password_too_short: function () {
            try {
                validator.validateUserPostRequest({
                    user: 'example@example.com', // email is user name
                    password: 'exa1', // 8 characters+, one alphanumeric
                    teamName: 'exampleTeamName', // name of team to display.
                    eventId: 'XZ3bw1fn44hr', // key assigned to event
                });
            }

            catch (exception) {
                if (exception === 'password is too short')
                    return true;
            }

            return false;
        },

        _user__post__teamName_empty: function () {
            try {
                validator.validateUserPostRequest({
                    user: 'example@example.com', // email is user name
                    password: 'examplePassword1', // 8 characters+, one alphanumeric
                    teamName: '',
                    eventId: 'XZ3bw1fn44hr', // key assigned to event
                });
            }

            catch (exception) {
                if (exception === 'teamName is null or empty')
                    return true;
            }

            return false;
        },

        _user__post__eventId_empty: function () {
            try {
                validator.validateUserPostRequest({
                    user: 'example@example.com', // email is user name
                    password: 'examplePassword1', // 8 characters+, one alphanumeric
                    teamName: 'exampleTeamName', // name of team to display.
                    eventId: '', // key assigned to event
                });
            }

            catch (exception) {
                if (exception === 'eventId is null or empty')
                    return true;
            }

            return false;
        },

        /**
         * Tests for `/user/remind` endpoint
         */

        _user_remind__post__positive: function () {
            validator.validateUserRemindPostRequest({
                user: 'example@example.com', // email is user name
            });

            return true;
        },

        _user_remind__post__bad_user: function () {
            try {
                validator.validateUserRemindPostRequest({
                    user: '123example.com', // email is user name
                });
            }

            catch (exception) {
                if (exception === 'user field is not email')
                    return true;
            }

            return false;
        },

        _user_remind__put__positive: function () {
            validator.validateUserRemindPutRequest({
                password: 'examplePassword1', // 8 characters+, one alphanumeric
            });

            return true;
        },

        _user_remind__put__password_without_number: function () {
            try {
                validator.validateUserRemindPutRequest({
                    password: 'examplePassword', // 8 characters+, one alphanumeric
                });
            }

            catch (exception) {
                if (exception === 'password has not number')
                    return true;
            }

            return false;
        },

        _user_remind__put__password_too_short: function () {
            try {
                validator.validateUserRemindPutRequest({
                    password: 'exa1', // 8 characters+, one alphanumeric
                });
            }

            catch (exception) {
                if (exception === 'password is too short')
                    return true;
            }

            return false;
        },

        /**
         * Tests for `/user/login` endpoint
         */

        _user_login__post__positive: function () {
        },

        _user_login__delete__positive: function () {
        },

        /**
         * Tests for `/event` endpoints
         */

        _event__get__positive: function () {
        },

        _event__post__positive: function () {
        },

        _event__put__positive: function () {
        },

        /**
         * Tests for `/event/collect` endpoints
         */

        _event_collect__put__positive: function () {
        },
    };
