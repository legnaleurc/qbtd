<div class="navbar navbar-fixed-top">
   <div class="navbar-inner">
      <div class="container">
      <a class="brand" href="<?php echo site_url(); ?>">Qbtd</a>

<?php if( $loggedin == true ): ?>
            <ul class="nav pull-right" >
            <li><a href="<?php echo site_url('user/logout'); ?>">Logout</a></li>
            </ul>

<?php else: ?>
            <ul class="nav pull-right" >
            <li><a href="<?php echo site_url('user/'); ?>">Regieter</a></li>
            <li><a href="<?php echo site_url('user/'); ?>">Login</a></li>
            </ul>
<?php endif; ?>
      </div>
   </div>
</div>
