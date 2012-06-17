<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>
<?php  $this->load->helper('url');  ?>

<h2>User Management</h2>
<p style="margin-top: 25px;"> </p>

<div class="span6 pull-center alert alert-error">
<h3><?php echo $error_title; ?></h3>
<p><?php echo $error_detail; ?></p>
<p><a href="<?php echo site_url('admin/'); ?>">&lt; Back</a></p>
</div>

<?php $this->load->view('footer');  ?>
