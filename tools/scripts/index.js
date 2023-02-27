/**
 * 
 */
function onBodyLoad() {
    // Bootstrap
    const tooltipTriggerList = document.querySelectorAll('[data-bs-toggle="tooltip"]');
    const toolTipList = [...tooltipTriggerList].map(x => new bootstrap.Tooltip(x));

    let index = 63;

    for (let rank = 8; rank >= 1; rank--) {
        let tr = document.getElementById(`rank${rank}TR`);

        tr.innerHTML = `<th>${rank}&nbsp;</th>`;

        for (let file = 97; file <= 104; file++) {
            tr.innerHTML += `
<td id="${String.fromCharCode(file)}${rank}TD">
  <div class="form-check">
    <input id="square${index}CheckBoxInput"
           class="form-check-input"
           type="checkbox"
           value=""
           title=""
           onchange="onCheckBoxInputChange()" />
  </div>
</td>`;
            index--;
        }
    }

    renderCode("0x0");
}

function getTextInput(base) {
    return document.getElementById(`base${base}TextInput`);
}

function getCheckBoxInput(index) {
    return document.getElementById(`square${index}CheckBoxInput`);
}

function getBits() {
    return BigInt(getTextInput(16).value)
        .toString(2)
        .padStart(64, '0')
        .split("");
}

function getValue(bits) {
    return BigInt("0b" + bits.join(""));
}

function onCheckBoxInputChange() {
    const bits = getBits();

    for (let i = 0; i < 64; i++) {
        if (getCheckBoxInput(i).checked) {
            bits[i] = '1';
        } else {
            bits[i] = '0';
        }
    }

    renderTextInputs(getValue(bits));
}

/**
 * 
 */
function onTextInputChange(base) {
    let value;
    const textInput = getTextInput(base);

    try {
        value = BigInt(textInput.value);
    } catch (error) {
        textInput.value = textInput.placeholder;

        return;
    }

    renderCheckBoxInputs(value.toString(2).split(""));
    renderTextInputs(value);
}

/**
 * 
 */
function onNotButtonClick() {
    const bits = getBits();

    for (let i = 0; i < 64; i++) {
        if (bits[i] == '1') {
            bits[i] = '0';
        } else {
            bits[i] = '1';
        }
    }

    renderCheckBoxInputs(bits);
    renderTextInputs(getValue(bits));
}

function renderCheckBoxInputs(bits) {
    for (let i = 0; i < 64; i++) {
        if (bits[i] == '1') {
            getCheckBoxInput(i).checked = true;
        } else {
            getCheckBoxInput(i).checked = false;
        }
    }
}

function renderTextInputs(value) {
    getTextInput(2).value = "0b" + value.toString(2);
    getTextInput(10).value = value.toString();

    const hex = "0x" + value.toString(16);

    getTextInput(16).value = hex;
    renderCode(hex);
}

function renderCode(hex) {
    let constant = document.getElementById("constantTextInput").value;

    if (constant == "") {
        constant = "BITBOARD";
    }

    document.getElementById("cCode").innerHTML = `#define ${constant.toUpperCase()} ${hex}`;
    hljs.highlightAll();
}

function onConstantTextInputChange() {
    renderCode(getTextInput(16).value);
}
