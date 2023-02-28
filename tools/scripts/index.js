var bitboard = 0n;

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
}

function getTextInput(base) {
    return document.getElementById(`base${base}TextInput`);
}

function getCheckBoxInput(index) {
    return document.getElementById(`square${index}CheckBoxInput`);
}

function onCheckBoxInputChange() {
    bitboard = 0n;

    for (let i = 0; i < 64; i++) {
        bitboard <<= 1n;

        if (getCheckBoxInput(i).checked) {
            bitboard++;
        }
    }

    renderText();
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

    bitboard = value;

    renderAll();
}

/**
 * 
 */
function onNotButtonClick() {
    let result = 0n;

    for (let bit of bitboard.toString(2).padStart(64, '0')) {
        result <<= 1n;

        if (bit == '0') {
            result++;
        }
    }

    bitboard = result;

    renderAll();
}

/**
 * 
 */
function onLeftShiftButtonClick() {
    bitboard <<= 1n;

    renderAll();
}

/**
 * 
 */
function onRightShiftButtonClick() {
    bitboard >>= 1n;

    renderAll();
}

function renderText() {
    getTextInput(2).value = "0b" + bitboard.toString(2).padStart(64, '0');
    getTextInput(10).value = bitboard.toString();
    getTextInput(16).value = "0x" + bitboard.toString(16);
}

function renderAll() {
    let i = 0;

    for (let bit of bitboard.toString(2).padStart(64, '0')) {
        if (bit == '1') {
            getCheckBoxInput(i).checked = true;
        } else {
            getCheckBoxInput(i).checked = false;
        }

        i++;
    }

    renderText();
}
