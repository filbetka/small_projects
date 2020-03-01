const tools = require('./validate-tools');


module.exports =
    {
        validateUserPostRequest: function (json) {
            if (tools.isNotEmail(json.user)) throw 'user field is not email';
            if (tools.isShorter(json.password, 8)) throw 'password is too short';
            if (tools.hasNotNumber(json.password)) throw 'password has not number';
            if (tools.isNullOrEmpty(json.teamName)) throw 'teamName is null or empty';
            if (tools.isNullOrEmpty(json.eventId)) throw 'eventId is null or empty';
        },

        validateUserRemindPostRequest: function (json) {
            if (tools.isNotEmail(json.user)) throw 'user field is not email';
        },

        validateUserRemindPutRequest: function (json) {
            if (tools.isShorter(json.password, 8)) throw 'password is too short';
            if (tools.hasNotNumber(json.password)) throw 'password has not number';
        },

        validateUserLoginPostRequest: function (json) {
            if (tools.isNotEmail(json.user)) throw 'user field is not email';
            if (tools.isShorter(json.password, 8)) throw 'password is too short';
            if (tools.hasNotNumber(json.password)) throw 'password has not number';
        },
    };
