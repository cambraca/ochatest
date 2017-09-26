<ul>
  <?php foreach ($content['values'] as $label => $item): ?>
    <li>
      <div class="value">
        <?php
        switch ($item['format'] ?: '') {
          <?php case 'currency_millions': ?>
            US$ <?php echo number_format($item['value'] / 1000000, 1); ?>M
            <?php break; ?>
          <?php case 'currency': ?>
            US$ <?php echo number_format($item['value'], 2); ?>
            <?php break; ?>
          <?php default: ?>
          <?php endswitch; ?>
      </div>
      <div class="label">
        <?php echo $label; ?>
      </div>
    </li>
  <?php endforeach; ?>
</ul>
