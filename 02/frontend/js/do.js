function verify_phone() {
    var value = document.getElementById('phone').value;
    var error = '';
    var error_msg = document.getElementById('phone_error');
    if (value.length != 11 || isNaN(value)) {
        error = '请输入有效的手机号';
    }
    error_msg.innerHTML = error;
    document.getElementById('search').disabled = !!error;
    return !error;
}

document.getElementById('phone').addEventListener('input', function (ev) {
    verify_phone();
});

document.getElementById('search').addEventListener('click', function (ev) {
    if (!verify_phone())
        ev.stopPropagation();
});