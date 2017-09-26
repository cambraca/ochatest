<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <ul>
    <?php foreach ($content['values'] as $label => $item): ?>
      <li>
        <div class="value">
          <?php
          switch (array_key_exists('format', $item) ? $item['format'] : '') {
            case 'currency_millions':
              echo 'US$ ' . number_format($item['value'] / 1000000, 1) . 'M';
              break;
            case 'currency':
              echo 'US$ ' . number_format($item['value'], 2);
              break;
            default:
              echo $item['value'];
          }
          ?>
        </div>
        <div class="label">
          <?php echo $label; ?>
        </div>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
