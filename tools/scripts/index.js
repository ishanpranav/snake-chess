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

    fetch("https://raw.githubusercontent.com/ishanpranav/snake-chess/main/src/bitboards.h")
        .then(response => response.text())
        .then(text => {
            const select = getConstantSelect();

            for (const match of text.matchAll(/#define ([A-Za-z_]+)_MASK (0x)?([0-9A-Fa-f]+)ull/g)) {
                select.innerHTML += `<option value="${BigInt("0x" + match[3]).toString(16)}">Bitmask: ${match[1].replaceAll('_', ' ').toLowerCase()}</option>`;
            }
        })
        .catch(error => console.log("Fetch Error :-S", error));
}

function getConstantSelect() {
    return document.getElementById("constantSelect");
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

function getBase2TextInput() {
    return document.getElementById("base2TextInput");
}

function getBase10TextInput() {
    return document.getElementById("base10TextInput");
}

function getBase16TextInput() {
    return document.getElementById("base16TextInput");
}

/**
 * 
 */
function onBase2TextInputChange() {
    const textInput = getBase2TextInput();

    if (!textInput.value.startsWith("0b")){
        textInput.value = "0b" + textInput.value;
    }

    onTextInputChange(textInput);
}

/**
 * 
 */
function onBase10TextInputChange() {
    return document.getElementById("base10TextInput");
}

/**
 * 
 */
function onBase16TextInputChange() {
    const textInput = document.getElementById("base16TextInput");

    if (!textInput.value.startsWith("0x")){
        textInput.value = "0x" + textInput.value;
    }
    
    onTextInputChange(textInput);
}

function onTextInputChange(textInput) {
    let value;

    if (textInput.value.endsWith("ull")) {
        textInput.value = textInput.value.substring(0, textInput.value.length - 3);
    }

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

    for (const bit of bitboard.toString(2).padStart(64, '0')) {
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
    getConstantSelect().value = bitboard.toString(16);
    getBase2TextInput().value = "0b" + bitboard.toString(2).padStart(64, '0');
    getBase10TextInput().value = bitboard.toString();
    getBase16TextInput().value = "0x" + bitboard.toString(16);
}

function renderAll() {
    let i = 0;

    for (const bit of bitboard.toString(2).padStart(64, '0')) {
        if (bit == '1') {
            getCheckBoxInput(i).checked = true;
        } else {
            getCheckBoxInput(i).checked = false;
        }

        i++;
    }

    renderText();
}

/**
 * 
 */
function onConstantSelectChange() {
    bitboard = BigInt("0x" + getConstantSelect().value);

    renderAll();
}
