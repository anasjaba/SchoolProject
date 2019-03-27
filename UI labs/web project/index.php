<?php

require_once __DIR__.'/vendor/autoload.php';

// Instanciate the application
$app = new Silex\Application();

/**
 * Configure the app
 */

// Debug
$app['debug'] = true;

// Registering the template system Twig
$app->register(new Silex\Provider\TwigServiceProvider(), array(
    'twig.path' => __DIR__.'/views',
));

// Register the URL Generator
$app->register(new Silex\Provider\UrlGeneratorServiceProvider());


/**
 * Here are the routes
 */

// Home
$app->get('/', function () use ($app) {
    return $app['twig']->render('roles.twig', array(
        'role' => 'any'
    ));
})
->bind('roles');

// Admin home page
$app->get('/admin', function () use ($app) {
    return $app['twig']->render('admin/dashboard.twig', array(
        'role' => 'admin'
    ));
})
->bind('admin_dashboard');

// Admin journals list
$app->get('/admin/journals', function () use ($app) {
    return $app['twig']->render('admin/journals.twig', array(
        'role' => 'admin'
    ));
})
->bind('admin_journals');

// Author dashboard
$app->get('/author', function () use ($app) {
    return $app['twig']->render('author/dashboard.twig', array(
        'role' => 'author'
    ));
})
->bind('author_dashboard');

// Author submissions
$app->get('/author/submissions', function () use ($app) {
    return $app['twig']->render('author/submissions.twig', array(
        'role' => 'author'
    ));
})
->bind('author_submissions');

// Author add new submissions
$app->get('/author/submissions/new', function () use ($app) {
    return $app['twig']->render('author/newSubmission.twig', array(
        'role' => 'author'
    ));
})
->bind('author_new_submission');

// Author submissions detail
$app->get('/author/submissions/{id}', function ($id) use ($app) {
    return $app['twig']->render('submissionDetail.twig', array(
        'role' => 'author',
        'id' => $app->escape($id)
    ));
})
->bind('author_submission_detail');

// Editor home page
$app->get('/editor', function () use ($app) {
    return $app['twig']->render('editor/dashboard.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_dashboard');

// Editor unassigned submissions
$app->get('/editor/unassigned', function () use ($app) {
    return $app['twig']->render('editor/unassigned.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_unassigned');

// Editor submissions in review
$app->get('/editor/inreview', function () use ($app) {
    return $app['twig']->render('editor/inreview.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_inreview');

// Editor submissions in editing
$app->get('/editor/inediting', function () use ($app) {
    return $app['twig']->render('editor/inediting.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_inediting');

// Editor assign reviewer
$app->get('/editor/assign', function () use ($app) {
    return $app['twig']->render('editor/assign.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_assign');

// Editor editing page
$app->get('/editor/editing', function () use ($app) {
    return $app['twig']->render('editor/editing.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_editing');

// Editor archives
$app->get('/editor/archives', function () use ($app) {
    return $app['twig']->render('editor/archives.twig', array(
        'role' => 'editor'
    ));
})
->bind('editor_archives');

// Editor submissions detail
$app->get('/editor/submissions/{id}', function ($id) use ($app) {
    return $app['twig']->render('submissionDetail.twig', array(
        'role' => 'editor',
        'id' => $app->escape($id)
    ));
})
->bind('editor_submission_detail');

// Editor journals list
$app->get('/editor/journals', function () use ($app) {
    return $app['twig']->render('editor/journals.twig', array(
        'role' => 'editor',
    ));
})
->bind('editor_journals');

// Reviewer home page
$app->get('/reviewer', function () use ($app) {
    return $app['twig']->render('reviewer/dashboard.twig', array(
        'role' => 'reviewer'
    ));
})
->bind('reviewer_dashboard');

// Reviewer inbox
$app->get('/reviewer/inbox', function () use ($app) {
    return $app['twig']->render('reviewer/inbox.twig', array(
        'role' => 'reviewer'
    ));
})
->bind('reviewer_inbox');

// Reviewer reviewing page
$app->get('/reviewer/reviewing', function () use ($app) {
    return $app['twig']->render('reviewer/reviewing.twig', array(
        'role' => 'reviewer'
    ));
})
->bind('reviewer_reviewing');

// Reviewer archives
$app->get('/reviewer/archives', function () use ($app) {
    return $app['twig']->render('reviewer/archives.twig', array(
        'role' => 'reviewer'
    ));
})
->bind('reviewer_archives');

// Reviewer review
$app->get('/reviewer/review', function () use ($app) {
    return $app['twig']->render('reviewer/review.twig', array(
        'role' => 'reviewer'
    ));
})
->bind('reviewer_review');


/**
 * Run the application
 */

$app->run();
