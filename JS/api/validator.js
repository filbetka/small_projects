const tools = require('./validate-tools');


module.exports =
    {
        validateUserPostRequest: function (json) {
            if (tools.isNotEmail(json['user'])) return false;
            if (tools.isShorter(json['password'], 8)) return false;
            if (tools.hasNotNumber(json['password'])) return false;
            if (tools.isNullOrEmpty(json['teamName'])) return false;
            if (tools.isNullOrEmpty(json['eventId'])) return false;
            return true;
        },

        validateUserRemindPostRequest: function (json) {
            if (tools.isNotEmail(json['user'])) return false;
            return true;
        },

        validateUserRemindPutRequest: function (json) {
            if (tools.isShorter(json['password'], 8)) return false;
            if (tools.hasNotNumber(json['password'])) return false;
            return true;
        },
    };
