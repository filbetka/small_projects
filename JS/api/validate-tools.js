
class ValidateTools {

    toJson(data) {
        try { return JSON.parse(data); }
        catch (error) {
            throw "Bad JSON format";
        }
    }

    hasNumber(data) {
        return /\d/.test(data);
    }

    hasNotNumber(data) {
        return !this.hasNumber(data);
    }

    isEmail(email) {
        let re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
        return re.test(String(email).toLowerCase());
    }

    isNotEmail(email) {
        return !this.isEmail(email);
    }

    isLonger(data, length) {
        return data.length > length;
    }

    isShorter(data, length) {
        return data.length < length;
    }

    isNullOrEmpty(data) {
        return data === '';
    }
}

// export
module.exports = new ValidateTools();
