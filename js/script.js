/* ============================
   MENU TABS - show/hide categories
   ============================ */
const tabButtons = document.querySelectorAll('.tab-btn');
const categories = document.querySelectorAll('.menu-category');

tabButtons.forEach(button => {
  button.addEventListener('click', () => {
    const selected = button.getAttribute('data-category');

    tabButtons.forEach(btn => btn.classList.remove('active'));
    button.classList.add('active');

    categories.forEach(cat => {
      cat.classList.toggle('active', cat.getAttribute('data-category') === selected);
    });
  });
});

/* ============================
   CART - array of {name, price, qty}
   ============================ */
let cart = [];

const cartCountEl = document.getElementById('cart-count');
const cartItemsEl = document.getElementById('cart-items');
const cartTotalEl = document.getElementById('cart-total');
const cartEmptyEl = document.getElementById('cart-empty');
const cartDropdown = document.getElementById('cart-dropdown');
const cartBtn = document.getElementById('cart-btn');

function updateCartUI() {
  const totalItems = cart.reduce((sum, item) => sum + item.qty, 0);
  cartCountEl.textContent = totalItems;
  cartItemsEl.innerHTML = '';

  if (cart.length === 0) {
    cartEmptyEl.style.display = 'block';
    cartTotalEl.textContent = '';
    return;
  }

  cartEmptyEl.style.display = 'none';

  let total = 0;
  cart.forEach((item) => {
    total += item.price * item.qty;
    const li = document.createElement('li');
    li.innerHTML = `
      <span>${item.name} x${item.qty} - Rs. ${item.price * item.qty}</span>
      <button class="remove-btn" data-name="${item.name}">Remove</button>
    `;
    cartItemsEl.appendChild(li);
  });

  cartTotalEl.textContent = `Total: Rs. ${total}`;
}
// Remove an item completely from the cart (clicked from the dropdown)
cartItemsEl.addEventListener('click', (e) => {
  if (!e.target.classList.contains('remove-btn')) return;

  const name = e.target.getAttribute('data-name');
  cart = cart.filter(i => i.name !== name);
  updateCartUI();

  // also reset that item's button back to "Add to Cart" on the Menu page
   // also reset that item's card back to a plain "Add to Cart" button
  const menuItem = document.querySelector(`.menu-item[data-name="${name}"]`);
  if (menuItem) {
    const actionDiv = menuItem.querySelector('.item-action');
    actionDiv.innerHTML = `<button class="add-cart-btn">Add to Cart</button>`;
  }
});
function findCartItem(name) {
  return cart.find(item => item.name === name);
}

function renderQtyControls(actionDiv, name) {
  const item = findCartItem(name);
  const qty = item ? item.qty : 0;

  actionDiv.innerHTML = `
    <div class="qty-controls">
      <button class="qty-btn qty-decrease">-</button>
      <span class="qty-value">${qty}</span>
      <button class="qty-btn qty-increase">+</button>
    </div>
  `;
}

// Event delegation - handles all Add to Cart, +, and - clicks
document.querySelector('.menu-section').addEventListener('click', (e) => {
  const menuItem = e.target.closest('.menu-item');
  if (!menuItem) return;

  const name = menuItem.getAttribute('data-name');
  const price = parseInt(menuItem.getAttribute('data-price'));
  const actionDiv = menuItem.querySelector('.item-action');

  // Clicked "Add to Cart" for the first time
  if (e.target.classList.contains('add-cart-btn')) {
    cart.push({ name, price, qty: 1 });
    renderQtyControls(actionDiv, name);
    updateCartUI();
    showToast('Item added to cart');
  }

  // Clicked the + button
  if (e.target.classList.contains('qty-increase')) {
    const item = findCartItem(name);
    item.qty += 1;
    renderQtyControls(actionDiv, name);
    updateCartUI();
  }

  // Clicked the - button
  if (e.target.classList.contains('qty-decrease')) {
    const item = findCartItem(name);
    item.qty -= 1;

    if (item.qty <= 0) {
      cart = cart.filter(i => i.name !== name);
      actionDiv.innerHTML = `<button class="add-cart-btn">Add to Cart</button>`;
    } else {
      renderQtyControls(actionDiv, name);
    }

    updateCartUI();
  }
});

// Toggle cart dropdown open/closed
cartBtn.addEventListener('click', () => {
  cartDropdown.classList.toggle('open');
});

/* ============================
   TOAST MESSAGE
   ============================ */
const toast = document.getElementById('toast');
let toastTimeout;

function showToast(message) {
  toast.textContent = message;
  toast.classList.add('show');

  clearTimeout(toastTimeout);
  toastTimeout = setTimeout(() => {
    toast.classList.remove('show');
  }, 2000);
}