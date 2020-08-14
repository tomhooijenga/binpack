<template>
  <div class="app container">
    <div class="card shadow-lg">
      <div class="card-body">
        <h1 class="display-4">Inhoud</h1>
        <p class="lead">
          Vul de dozen in die je gaat versturen. De maten zijn in cm.
          Een doos heeft een maximaal formaat van 140 x 78 x 58 cm en een maximaal gewicht van 30 kilo.
        </p>

        <section v-for="item in items"
                 :key="item.name"
                 @input="update"
                 class="form-group form-row">
          <div class="col-auto">
            <span class="valid-icon"
                  :class="{'is-valid': !invalidItems.has(item), 'is-invalid': invalidItems.has(item)}">
            </span>
          </div>
          <div class="col">
            <div class="input-group">
              <input type="number"
                     class="form-control"
                     min="0"
                     v-model.number="item.width" />
              <div class="input-group-middle">
                <span class="input-group-text">&times;</span>
              </div>
              <input type="number"
                     class="form-control"
                     min="0"
                     v-model.number="item.depth" />
              <div class="input-group-middle">
                <span class="input-group-text">&times;</span>
              </div>
              <input type="number"
                     class="form-control"
                     min="0"
                     v-model.number="item.height" />
            </div>
          </div>
          <div class="w-100 d-block d-md-none"></div>

          <div class="col-auto ml-auto">
            <button type="button"
                    class="btn btn-outline-primary"
                    @click="copyItem(item)"
                    v-text="'Kopiëer'" />
          </div>
          <div class="col-auto">
            <button type="button"
                    class="btn btn-outline-danger"
                    @click="deleteItem(item)"
                    :disabled="items.length === 1"
                    v-text="'Verwijder'"/>
          </div>
        </section>

        <hr class="my-5"/>

        <h1 class="text-center">
              <span class="display-1"
                    v-text="bins"/>
          <br/>
          <small v-if="bins === 1">rolcontainer</small>
          <small v-else>rolcontainers</small>
        </h1>
      </div>
    </div>
  </div>
</template>

<script>
  import {pack, Item} from './pack'

  // https://www.myparcel.nl/product/dubbelgolf-verzenddoos-300-x-300-x-160-mm/
  const defaultItem = [30, 16, 30, 3]
  // Dimensions are ordered in size, weight is last.
  const maxItem = [58, 78, 140, 30]

  export default {
    name: 'App',
    components: {},

    data() {
      return {
        items: [new Item(...defaultItem)],
        bins: 1,
        invalidItems: new Set(),
      }
    },

    methods: {
      copyItem(item) {
        const newItem = new Item(item.width, item.height, item.depth);
        const index = this.items.indexOf(item);

        this.items.splice(index, 0, newItem);
        this.update();
      },
      deleteItem(item) {
        this.items = this.items.filter((i) => i !== item);
        this.update();
      },
      update() {
        const items = this.validItems();

        this.updateValidation(items);
        this.pack(items);
      },
      updateValidation(validItems) {
        const validItemsSet = new Set(validItems);
        const invalidItems = this.items.filter((item) => !validItemsSet.has(item))
        this.invalidItems = new Set(invalidItems);
      },
      validItems() {
        function between(max, val) {
          return val >= 0 && val <= max;
        }
        return this.items.filter(({width, height, depth}) => {
          // It doesn't matter which side has which length, as long as they all fit.
          const size = [width, height, depth].sort((a, b) => a - b);

          return between(maxItem[0], size[0])
          && between(maxItem[1], size[1])
          && between(maxItem[2], size[2]);
        })
      },
      async pack(items) {
        this.bins = await pack(items);
      }
    }
  }
</script>

<style lang="scss">
  $font-weight-base: 300;
  $border-radius: 30px;
  $card-spacer-x: 3rem;
  $card-spacer-y: 3rem;
  @import "~bootstrap/scss/bootstrap-reboot";
  @import "~bootstrap/scss/buttons";
  @import "~bootstrap/scss/card";
  @import "~bootstrap/scss/forms";
  @import "~bootstrap/scss/grid";
  @import "~bootstrap/scss/input-group";
  @import "~bootstrap/scss/type";
  @import "~bootstrap/scss/utilities/shadows";
  @import "~bootstrap/scss/utilities/display";
  @import "~bootstrap/scss/utilities/spacing";
  @import "~bootstrap/scss/utilities/sizing";
  @import "~bootstrap/scss/utilities/text";

  body::before {
    content: '';
    display: block;
    top: 0;
    width: 100%;
    height: 30vh;
    position: absolute;
    background-color: #0F5C47;
    background-image: url(./assets/bg-shape-right.svg);
  }

  .app {
    display: flex;
    padding-top: 15vh;
    flex-direction: column;
    justify-content: center;
    align-content: center;
  }

  .input-group-middle > .input-group-text {
    border-width: 1px 0;
    border-radius: 0;
  }

  .valid-icon {
    display: inline-block;
    height: $input-height;
    width: $input-height-inner-half;
    background-repeat: no-repeat;
    background-position: center center;
    background-size: $input-height-inner-half $input-height-inner-half;

    &.is-valid {
      background-image: escape-svg($form-feedback-icon-valid);
    }
    &.is-invalid {
      background-image: escape-svg($form-feedback-icon-invalid);
    }
  }
</style>
